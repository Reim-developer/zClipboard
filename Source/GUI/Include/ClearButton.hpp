#ifndef CLEAR_BUTTON_HPP
#define CLEAR_BUTTON_HPP

#include <QGridLayout>
#include <QPushButton>
#include <QObject>
#include "TableView.hpp"
#include <QSettings>
#include "../../Lib_Memory/Include/Memory.hpp"
#include "../../Core/Include/CoreClearCache.hpp"
#include "../../Utils/Include/Namespace_Macro.hpp"
#include "../Toolkit/Include/MainWindow_Components.hpp"

#if defined (Z_DEBUG)
    #include "../../Utils/Include/Logging.hpp"
    using ZClipboard::AppUtils::LogContext;
#endif

using ZClipboard::GUI::TableView;
using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::Core::CoreClearBuilder;
using ZClipboard::GUI::Toolkit::MainWindowComponentsManager;

GUI_NAMESPACE

    class ClearButton  {
        private:
            PtrUnique<CoreClearBuilder> BuilderCore;
        
        private:
            using ComponentsManager = MainWindowComponentsManager;

        public:
            void SetupClearButton(ComponentsManager *toolkit, TableView *tableView);
            
        private:
            void SetupEventListener(QPushButton *clearButton, TableView *tableView);
        
        private:
            PtrUnique<QSettings> settings;

        #if defined (Z_DEBUG)
            private:
                void __LOGGING_ALL_OBJECTS__(QPushButton *clearButton) {
                    LogContext{}.LogDebug(&BuilderCore);
                    LogContext{}.LogDebug(&settings);
                    LogContext{}.LogDebug(&clearButton);
                }

        #endif
    };

END_NAMESPACE

#endif  // CLEAR_BUTTON_HPP