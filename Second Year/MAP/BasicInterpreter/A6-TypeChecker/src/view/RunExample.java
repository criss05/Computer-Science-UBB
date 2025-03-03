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
            this.controller.allStep();
        }catch(RepoException err){
            System.out.println(err.getMessage());
        } catch (InterruptedException | RuntimeException e) {
            throw new RuntimeException(e);
        }
    }
}
