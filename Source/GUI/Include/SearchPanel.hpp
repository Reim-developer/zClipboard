#ifndef zSearchPanel_HPP
#define zSearchPanel_HPP
#include <QMainWindow>
#include <QLineEdit>
#include <QGridLayout>
#include "TableModel.hpp"
#include "TableView.hpp"
#include "../../Utils/Include/Namespace_Macro.hpp"
#include "../Toolkit/Include/MainWindow_Components.hpp"
#include "../../Utils/Include/Meta_Macro.hpp"
#include "../../Utils/Include/Utils.hpp"
#include "../../Lib_Memory/Include/Memory.hpp"

using ZClipboard::GUI::TableView;
using ZClipboard::GUI::TableModel;
using ZClipboard::GUI::Toolkit::MainWindowComponentsManager;
using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::AppUtils::Utils;

GUI_NAMESPACE
    struct SearchAreaImpl {
        TableView *tableView;
        MainWindowComponentsManager *componentsManager;
    };

    class SearchArea {

    private:
        PtrUnique<SearchAreaImpl> Impl;
        using Implement = SearchAreaImpl;

    public:
        SearchArea *StartBuild();
        
        CLASS_BUILD(T, V)
        SearchArea *WithAndThen(T Implement::*member, V &&value) {
            Impl.get()->*member = FORWARD(V, value);

            return this;
        }

        SearchArea *WhenDone();

        void SetupSearchPanel();
        QLineEdit *GetSearchPanel();
    };

END_NAMESPACE

#endif  // zSearchPanel_HPP