module com.example.a7gui {
    requires javafx.controls;
    requires javafx.fxml;
    requires javafx.base;


    exports com.example.a7gui;
    exports com.example.a7gui.sceneController;

    opens com.example.a7gui to javafx.fxml;
    opens com.example.a7gui.sceneController to javafx.fxml;
    opens com.example.a7gui.repository to javafx.base;
    opens com.example.a7gui.tableViewModels to javafx.base;
}