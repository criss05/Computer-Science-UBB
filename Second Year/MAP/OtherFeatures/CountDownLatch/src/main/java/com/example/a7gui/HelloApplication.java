package com.example.a7gui;

import com.example.a7gui.sceneController.StartPageController;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("StartPage.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 700, 300);
        StartPageController controller = fxmlLoader.getController();
        controller.setPrevStage(stage);


        stage.setTitle("Toy Language Interpreter App");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}