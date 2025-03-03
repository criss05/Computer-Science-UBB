package view;

import model.expression.AritmeticalExpression;
import model.expression.AritmeticalOperator;
import model.expression.ValueExpression;
import model.expression.VariableExpression;
import model.state.PrgState;
import model.statement.*;
import model.types.BoolType;
import model.types.IntType;
import model.types.StringType;
import model.value.BoolValue;
import model.value.IntValue;
import model.value.StringValue;
import repository.IRepository;
import repository.MyRepository;
import controller.Controller;

public class Interpreter {
    public static void run() {
        //int v; v=2;Print(v)
        IStatement ex1 = new CompStatement(new VarDeclStatement("v", new IntType()), new CompStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(2))), new PrintStatement(new VariableExpression("v"))));
        PrgState prg1 = new PrgState(ex1);
        IRepository repo1 = new MyRepository("file1.txt");
        repo1.addPrg(prg1);
        Controller controller1 = new Controller(repo1);

        //int a;int b; a=2+3*5;b=a+1;Print(b)
        IStatement ex2 = new CompStatement(new VarDeclStatement("a", new IntType()), new CompStatement(new VarDeclStatement("b", new IntType()), new CompStatement(new AssignmentStatement("a", new AritmeticalExpression(new ValueExpression(new IntValue(2)), AritmeticalOperator.ADD, new AritmeticalExpression(new ValueExpression(new IntValue(3)), AritmeticalOperator.MULTIPLY, new ValueExpression(new IntValue(5))))), new CompStatement(new AssignmentStatement("b", new AritmeticalExpression(new VariableExpression("a"), AritmeticalOperator.ADD, new ValueExpression(new IntValue(1)))), new PrintStatement(new VariableExpression("b"))))));
        PrgState prg2 = new PrgState(ex2);
        IRepository repo2 = new MyRepository("file2.txt");
        repo2.addPrg(prg2);
        Controller controller2 = new Controller(repo2);

        //bool a;int v; a=true; (If a Then v=2 Else v=3); Print(v)
        IStatement ex3 = new CompStatement(new VarDeclStatement("a", new BoolType()), new CompStatement(new VarDeclStatement("v", new IntType()), new CompStatement(new AssignmentStatement("a", new ValueExpression(new BoolValue(true))), new CompStatement(new IfStatement(new VariableExpression("a"), new AssignmentStatement("v", new ValueExpression(new IntValue(2))), new AssignmentStatement("v", new ValueExpression(new IntValue(3)))), new PrintStatement(new VariableExpression("v"))))));
        PrgState prg3 = new PrgState(ex3);
        IRepository repo3 = new MyRepository("file3.txt");
        repo3.addPrg(prg3);
        Controller controller3 = new Controller(repo3);

        // string varf; varf="test.in"; openRFile(varf); int varc; readFile(varf, varc); print(varc);
        // readFile(varf, varc); print(varc); closeRFile(varf)
        IStatement ex4 = new CompStatement(new VarDeclStatement("varf", new StringType()),
                new CompStatement(new AssignmentStatement("varf", new ValueExpression(new StringValue("test.in"))),
                        new CompStatement(new OpenRFileStatement(new VariableExpression("varf")),
                                new CompStatement(new VarDeclStatement("varc", new IntType()),
                                        new CompStatement(new ReadFileStatement(new VariableExpression("varf"), "varc"),
                                                new CompStatement(new PrintStatement(new VariableExpression("varc")),
                                                        new CompStatement(new ReadFileStatement(new VariableExpression("varf"), "varc"),
                                                                new CompStatement(new PrintStatement(new VariableExpression("varc")), new CloseRFileStatement(new VariableExpression("varf"))))))))));
        PrgState prg4 = new PrgState(ex4);
        IRepository repo4 = new MyRepository("file4.txt");
        repo4.addPrg(prg4);
        Controller controller4 = new Controller(repo4);

        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0", "exit"));
        menu.addCommand(new RunExample("1", ex1.toString(), controller1 ));
        menu.addCommand(new RunExample("2", ex2.toString(), controller2 ));
        menu.addCommand(new RunExample("3", ex3.toString(), controller3 ));
        menu.addCommand(new RunExample("4", ex4.toString(), controller4));
        menu.show();
    }
}
