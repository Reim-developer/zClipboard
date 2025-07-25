#ifndef LAYOUT_MANAGER_TOOLKIT_HPP
#define LAYOUT_MANAGER_TOOLKIT_HPP
#include "../../../Utils/Include/Namespace_Macro.hpp"
#include "../../../Lib_Memory/Include/Memory.hpp"
#include "../../../Utils/Include/Meta_Macro.hpp"
#include "MainWindow_Components.hpp"
#include "Layout_Toolkit.hpp"
#include <QGridLayout>

using ZClipboard::GUI::Toolkit::MainWindowComponentsManager;
using ZClipboard::Lib_Memory::PtrUnique;

#if defined (Z_DEBUG)
    #include "../../../Utils/Include/Logging.hpp"
    using ZClipboard::AppUtils::LogContext;
#endif

GUI_TOOLKIT_NAMESPACE

    struct MainWindowLayoutData {
        QGridLayout *layout;
        MainWindowComponentsManager *tookit;
    };

    class MainWindowLayoutManager {
        private:
            using Self = MainWindowLayoutManager;
            using ImplData = MainWindowLayoutData;
            using Toolkit  = MainWindowComponentsManager;
            using Widget = WidgetProperty;

        private:
            PtrUnique<ImplData> Impl;
            QGridLayout *GetGridLayout();
            Toolkit *GetTookit();

        /*
        * Application widget layout data.
        */
        private:
            Widget GetTableViewLayout(Toolkit *tookit); 
            Widget GetSearchAreaLayout(Toolkit *tookit);
            Widget GetConnectButtonLayout(Toolkit *toolkit);
            Widget GetDisconnectButtonLayout(Toolkit *toolkit);
            Widget GetClearButtonLayout(Toolkit *toolkit);
            Widget GetSettingButtonLayout(Toolkit *toolkit);

        public:
            Self *StartBuild();

            CLASS_BUILD(T, V)
            Self *WithAndThen(T ImplData::*member, V &&value) {
                Impl.get()->*member = FORWARD(V, value);

                return this;
            }

            Self *WhenDone();

            void SetupAppGridLayout();
        
        #if defined (Z_DEBUG)
            private:
                void __LOGGING_ALL_OBJECTS__() {
                    LogContext{}.LogDebug(&Impl->layout);
                    LogContext{}.LogDebug(&Impl->layout);
                }
        #endif
    };

END_NAMESPACE
#endif // LAYOUT_MANAGER_TOOLKIT_HPP