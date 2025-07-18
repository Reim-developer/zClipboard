import json

def utf8_to_hex(string: str) -> str:
    return "".join(f'\\x{b:02x}' for b in string.encode("utf-8"))

with open(file = "./test.json", mode = "r", encoding = "utf-8") as jsonData:
    data = json.load(jsonData)
    
    with open(file = "result_test_.hpp", mode = "w", encoding = "utf-8") as headerFile:
        headerFile.write("#ifndef RESULT_TEST_HPP\n")
        headerFile.write("#define RESULT_TEST_HPP\n\n")

        languages = data.get("Language", {})

        for language, string in languages.items():
            struct_name = f"Language_{language}"
            
            headerFile.write("/* Auto generated by zClipboard Toolchain. */\n")
            headerFile.write(f"/* Struct: {struct_name}, for language: {language} */\n")
            headerFile.write(f"struct {struct_name} {{\n")
            for key, value in string.items():
                hex_value = utf8_to_hex(value)
                headerFile.write(f"     /* Expands to: {value} */\n\n")
                headerFile.write(f'     static inline const constexpr char* {key} = "{hex_value}";\n\n')

            headerFile.write("};\n\n")

        headerFile.write("#endif // RESULT_TEST_HPP")