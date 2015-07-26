ApplicationWindow {
        id: window
        menuBar: MenuBar {
            Menu { MenuItem {...} }
            Menu { MenuItem {...} }
        }

        toolBar: ToolBar {
            RowLayout {
                anchors.fill: parent
                ToolButton {...}
            }
        }

        TabView {
            id: myContent
            anchors.fill: parent
            ...
        }
    }
