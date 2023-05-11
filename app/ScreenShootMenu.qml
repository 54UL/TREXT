import QtQuick
import QtQuick.Controls
import Qt.labs.platform
import QtQuick.Layouts

    MenuBar {
        id: underlyingMenuBar
        Menu {
            title: "File"

            Item {
                MenuItem {
                    text: "New"
                    onTriggered: {
                        // Handle "New" action
                    }
                }

                MenuItem {
                    text: "Open"
                    onTriggered: {
                        // Handle "Open" action
                    }
                }

                MenuItem {
                    text: "Save"
                    onTriggered: {
                        // Handle "Save" action
                    }
                }

                MenuItem {
                    text: "Save As"
                    onTriggered: {
                        // Handle "Save As" action
                    }
                }

                MenuItem {
                    text: "Print"
                    onTriggered: {
                        // Handle "Print" action
                    }
                }

                MenuItem {
                    text: "Exit"
                    onTriggered: {
                        // Handle "Exit" action
                    }
                }
            }
        }

        Menu {
            title: "Edit"

            Item {
                MenuItem {
                    text: "Undo"
                    onTriggered: {
                        // Handle "Undo" action
                    }
                }

                MenuItem {
                    text: "Redo"
                    onTriggered: {
                        // Handle "Redo" action
                    }
                }
            }
        }
    }



