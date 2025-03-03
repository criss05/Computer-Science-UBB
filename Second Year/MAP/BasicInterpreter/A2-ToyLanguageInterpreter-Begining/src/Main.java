import exception.*;
import view.Interpreter;

public class Main {
    public static void main(String[] args) {
        try {
            Interpreter.run();
        }catch(StatementException | ADTException | ExpressionException | RepoException | VariableAlreadyExists err){
            System.out.println(err.getMessage());
        }
    }
}