package com.example.a7gui.sceneController;

import com.example.a7gui.HelloApplication;
import com.example.a7gui.exception.ExpressionException;
import com.example.a7gui.exception.KeyNotFoundException;
import com.example.a7gui.exception.StatementException;
import com.example.a7gui.model.adt.MySymTable;
import com.example.a7gui.model.expression.*;
import com.example.a7gui.model.statement.*;
import com.example.a7gui.model.types.BoolType;
import com.example.a7gui.model.types.IntType;
import com.example.a7gui.model.types.RefType;
import com.example.a7gui.model.types.StringType;
import com.example.a7gui.model.value.BoolValue;
import com.example.a7gui.model.value.IntValue;
import com.example.a7gui.model.value.StringValue;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.layout.StackPane;
import javafx.stage.Modality;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class StartPageController {
    @FXML
    private ListView<String> programsListView;
    @FXML
    private Button runButton;

    private List<IStatement> listStatement = new ArrayList<>();
    private IStatement currentStatement;
    private Stage prevStage;
    private int fieldIndex;

    @FXML
    public void initialize(){
        IStatement ex1 = new CompStatement(new VarDeclStatement("v", new IntType()), new CompStatement(new AssignmentStatement("v", new ValueExpression(new StringValue("ccc"))), new PrintStatement(new VariableExpression("v"))));
        IStatement ex2 = new CompStatement(new VarDeclStatement("a", new IntType()), new CompStatement(new VarDeclStatement("b", new IntType()), new CompStatement(new AssignmentStatement("a", new ArithmeticalExpression(new ValueExpression(new IntValue(2)), ArithmeticalOperator.ADD, new ArithmeticalExpression(new ValueExpression(new IntValue(3)), ArithmeticalOperator.MULTIPLY, new ValueExpression(new IntValue(5))))), new CompStatement(new AssignmentStatement("b", new ArithmeticalExpression(new VariableExpression("a"), ArithmeticalOperator.ADD, new ValueExpression(new IntValue(1)))), new PrintStatement(new VariableExpression("b"))))));
        IStatement ex3 = new CompStatement(new VarDeclStatement("a", new BoolType()), new CompStatement(new VarDeclStatement("v", new IntType()), new CompStatement(new AssignmentStatement("a", new ValueExpression(new BoolValue(true))), new CompStatement(new IfStatement(new VariableExpression("a"), new AssignmentStatement("v", new ValueExpression(new IntValue(2))), new AssignmentStatement("v", new ValueExpression(new IntValue(3)))), new PrintStatement(new VariableExpression("v"))))));
        IStatement ex4 = new CompStatement(new VarDeclStatement("varf", new StringType()), new CompStatement(new AssignmentStatement("varf", new ValueExpression(new StringValue("test.in"))), new CompStatement(new OpenRFileStatement(new VariableExpression("varf")), new CompStatement(new VarDeclStatement("varc", new IntType()), new CompStatement(new ReadFileStatement(new VariableExpression("varf"), "varc"), new CompStatement(new PrintStatement(new VariableExpression("varc")), new CompStatement(new ReadFileStatement(new VariableExpression("varf"), "varc"), new CompStatement(new PrintStatement(new VariableExpression("varc")), new CloseRFileStatement(new VariableExpression("varf"))))))))));
        IStatement ex5=new CompStatement(new VarDeclStatement("v", new RefType(new IntType())), new CompStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))), new CompStatement(new PrintStatement(new ReadHeapExpression(new VariableExpression("v"))), new CompStatement(new HeapWritingStatement("v",new ValueExpression(new IntValue(30))), new PrintStatement(new ArithmeticalExpression(new ReadHeapExpression(new VariableExpression("v")), ArithmeticalOperator.ADD,new ValueExpression(new IntValue(5))))))));
        IStatement ex6=new CompStatement(new VarDeclStatement("v", new RefType(new IntType())), new CompStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))), new CompStatement(new VarDeclStatement("a", new RefType(new RefType(new IntType()))), new CompStatement(new HeapAllocationStatement("a", new VariableExpression("v")), new CompStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(30))), new PrintStatement(new ReadHeapExpression(new ReadHeapExpression(new VariableExpression("a")))))))));
        IStatement ex7=new CompStatement(new VarDeclStatement("v", new RefType(new IntType())), new CompStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))), new CompStatement(new PrintStatement(new ReadHeapExpression(new VariableExpression("v"))), new CompStatement(new HeapWritingStatement("v",new ValueExpression(new IntValue(30))), new CompStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(50))), new PrintStatement(new ArithmeticalExpression(new ReadHeapExpression(new VariableExpression("v")), ArithmeticalOperator.ADD,new ValueExpression(new IntValue(5)))))))));
        IStatement ex8=new CompStatement(new VarDeclStatement("v", new IntType()), new CompStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(4))), new CompStatement(new WhileStatement(new RelationalExpression(new VariableExpression("v"), RelationalOperator.GRATER, new ValueExpression(new IntValue(0))), new CompStatement(new PrintStatement(new VariableExpression("v")), new AssignmentStatement("v", new ArithmeticalExpression(new VariableExpression("v"), ArithmeticalOperator.SUBTRACT, new ValueExpression(new IntValue(1)))))), new PrintStatement(new VariableExpression("v")))));
        IStatement ex9 = new CompStatement(new VarDeclStatement("v", new IntType()), new CompStatement(new VarDeclStatement("a", new RefType(new IntType())), new CompStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(10))), new CompStatement(new HeapAllocationStatement("a", new ValueExpression(new IntValue(22))), new CompStatement(new ForkStatement(new CompStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(72))), new CompStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(32))), new CompStatement(new PrintStatement(new VariableExpression("v")), new PrintStatement(new ReadHeapExpression(new VariableExpression("a"))))))), new CompStatement(new PrintStatement(new VariableExpression("v")), new PrintStatement(new ReadHeapExpression(new VariableExpression("a")))))))));

        listStatement.add(ex1);
        listStatement.add(ex2);
        listStatement.add(ex3);
        listStatement.add(ex4);
        listStatement.add(ex5);
        listStatement.add(ex6);
        listStatement.add(ex7);
        listStatement.add(ex9);

        for (IStatement statement : listStatement){
            programsListView.getItems().add(statement.toString());
        }

        programsListView.getSelectionModel().selectedItemProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observableValue, String s, String t1) {
                fieldIndex = programsListView.getSelectionModel().getSelectedIndex();
                currentStatement = listStatement.get(fieldIndex);
            }
        });

        programsListView.getSelectionModel().select(0);
        fieldIndex = 0;
        runButton.setOnAction(this::runButtonHandler);
    }

    public void setPrevStage(Stage prevStage) {
        this.prevStage = prevStage;
    }

    @FXML
    private void runButtonHandler(ActionEvent event){
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("ProgramPage.fxml"));

        Parent root;
        Scene scene;

        try {
            this.currentStatement.typeCheck(new MySymTable<>());
            root = fxmlLoader.load();
            scene = new Scene(root, 1000, 500);
        } catch (KeyNotFoundException | ExpressionException | StatementException | IOException e) {
            Stage errorStage = new Stage();
            errorStage.setTitle("Error");
            errorStage.initModality(Modality.WINDOW_MODAL);
            errorStage.initOwner(prevStage);
            errorStage.setScene(new Scene(new StackPane(new Label("Error: "+e.getMessage())), 500, 300));
            errorStage.show();
            return;
        }
        Stage newWindow = new Stage();
        newWindow.setTitle("Running program " + (fieldIndex+1));
        newWindow.setScene(scene);
        newWindow.initModality(Modality.WINDOW_MODAL);
        newWindow.initOwner(prevStage);
        ProgramPageController programPageController = fxmlLoader.getController();
        programPageController.setPrevStage(newWindow);
        programPageController.setInitialStatement(this.currentStatement);
        newWindow.setOnCloseRequest(e->{
            programPageController.stopExecution();
        });
        newWindow.show();

    }
}
