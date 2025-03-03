package view;

import controller.Controller;
import exception.*;


public class RunExample extends Command{
    private Controller controller;
    public RunExample(String key, String description, Controller controller) {
        super(key, description);
        this.controller=controller;
    }

    @Override
    public void execute() {
        try{
            this.controller.allSteps();
        }catch(ADTException | ExpressionException | RepoException | StatementException | VariableAlreadyExists err){
            System.out.println(err.getMessage());
        }
    }
}
