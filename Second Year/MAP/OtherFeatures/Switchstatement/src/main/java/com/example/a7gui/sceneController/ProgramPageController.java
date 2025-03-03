package com.example.a7gui.sceneController;

import com.example.a7gui.controller.Controller;
import com.example.a7gui.exception.ControllerException;
import com.example.a7gui.exception.RepoException;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.statement.IStatement;
import com.example.a7gui.model.value.IValue;
import com.example.a7gui.repository.IRepository;
import com.example.a7gui.repository.MyRepository;
import com.example.a7gui.tableViewModels.HeapTableViewModel;
import com.example.a7gui.tableViewModels.SymTableViewModel;
import javafx.application.Platform;
import javafx.beans.InvalidationListener;
import javafx.beans.Observable;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.StackPane;
import javafx.stage.Modality;
import javafx.stage.Stage;

public class ProgramPageController {
    @FXML
    private Button runStepButton;
    @FXML
    private TableView<SymTableViewModel> symTableView;
    @FXML
    private TableColumn<SymTableViewModel, String> symTableNameColumn;
    @FXML
    private TableColumn<SymTableViewModel, IValue> symTableValueColumn;
    @FXML
    private ListView<String> outputListView;
    @FXML
    private TextField noPrgsTextField;
    @FXML
    private TableView<HeapTableViewModel> heapTableView;
    @FXML
    private TableColumn<HeapTableViewModel, Integer> heapAddressColumn;
    @FXML
    private TableColumn<HeapTableViewModel, IValue> heapValueColumn;
    @FXML
    private ListView<String> fileTableListView;
    @FXML
    private ListView<String> exeStackListView;
    @FXML
    private ListView<String> programIdListView;

    private IRepository repository;
    private Controller controller;
    private PrgState currentPrgState;
    private IStatement initialStatement;
    private Stage prevStage;

    InvalidationListener listener = new InvalidationListener() {
        @Override
        public void invalidated(Observable observable) {
            update();
        }
    };

    public void initialize(){
        Platform.runLater(()->{
            repository = new MyRepository("file.txt");
            try{
                repository.ClearFile();
            } catch (RepoException e) {
                Stage errorStage = new Stage();
                errorStage.setTitle("Error");
                errorStage.initModality(Modality.WINDOW_MODAL);
                errorStage.initOwner(prevStage);
                errorStage.setScene(new Scene(new StackPane(new Label("Error: "+e.getMessage())), 500, 300));
                errorStage.show();
                return;
            }
            this.currentPrgState = new PrgState(this.initialStatement);
            this.currentPrgState.init();
            this.repository.addPrg(this.currentPrgState);
            this.repository.addListener(this.listener);
            this.controller = new Controller(this.repository);
            this.controller.startThreads();

            this.heapAddressColumn.setCellValueFactory(new PropertyValueFactory<>("HeapAddress"));
            this.heapValueColumn.setCellValueFactory(new PropertyValueFactory<>("HeapValue"));
            this.symTableNameColumn.setCellValueFactory(new PropertyValueFactory<>("SymName"));
            this.symTableValueColumn.setCellValueFactory(new PropertyValueFactory<>("SymValue"));

            this.programIdListView.getSelectionModel().selectedItemProperty().addListener(new ChangeListener<String>() {
                @Override
                public void changed(ObservableValue<? extends String> observableValue, String s, String t1) {
                    int selectedIndex = programIdListView.getSelectionModel().getSelectedIndex();
                    if(selectedIndex>=0){
                        currentPrgState = repository.getPrgList().get(selectedIndex);
                        populateUncommonViews();
                    }
                }
            });
            update();
            runStepButton.setOnAction(this::runStepButtonHandler);
        });
    }

    private void runStepButtonHandler(ActionEvent actionEvent){
        try {
            this.controller.oneStepGUI();
        } catch (ControllerException e) {
            Stage errorStage = new Stage();
            errorStage.setTitle("Error");
            errorStage.initModality(Modality.WINDOW_MODAL);
            errorStage.initOwner(prevStage);
            errorStage.setScene(new Scene(new StackPane(new Label("Error: "+e.getMessage())), 500, 300));
            errorStage.show();
        }
    }

    private void populateUncommonViews() {
        this.symTableView.getItems().setAll(this.currentPrgState.getSymTable().getMap().entrySet().stream().map(e-> new SymTableViewModel(e.getKey(), e.getValue())).toList());
        this.exeStackListView.getItems().setAll(this.currentPrgState.getExeStack().toStringGUI2());
    }

    public void update(){
        this.noPrgsTextField.setText("Number of programs: " + this.repository.getPrgList().size());
        this.heapTableView.getItems().setAll(this.currentPrgState.getHeap().getMap().entrySet().stream().map(e-> new HeapTableViewModel(e.getKey(), e.getValue())).toList());
        this.symTableView.getItems().setAll(this.currentPrgState.getSymTable().getMap().entrySet().stream().map(e-> new SymTableViewModel(e.getKey(), e.getValue())).toList());
        this.fileTableListView.getItems().setAll(this.currentPrgState.getFileTable().toStringGUI());
        this.outputListView.getItems().setAll(this.currentPrgState.getOutput().toStringGUI());
        this.exeStackListView.getItems().setAll(this.currentPrgState.getExeStack().toStringGUI2());
        this.programIdListView.getItems().setAll(this.repository.getPrgList().stream().map(e->Integer.toString(e.getID())).toList());
    }

    public void setInitialStatement(IStatement initialStatement) {
        this.initialStatement = initialStatement;
    }

    public void setPrevStage(Stage prevStage) {
        this.prevStage = prevStage;
    }

    public void stopExecution(){
        this.controller.endThreads();
    }
}
