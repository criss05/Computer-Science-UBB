package view;

import exception.ExpressionException;
import exception.KeyNotFoundException;
import exception.StatementException;
import model.adt.MySymTable;
import model.expression.*;
import model.state.PrgState;
import model.statement.*;
import model.types.*;
import model.value.BoolValue;
import model.value.IntValue;
import model.value.StringValue;
import repository.IRepository;
import repository.MyRepository;
import controller.Controller;

import java.security.interfaces.RSAMultiPrimePrivateCrtKey;

public class Interpreter {
    public static void run() {
        //int v; v=2;Print(v)
        IStatement ex1 = new CompStatement(new VarDeclStatement("v", new IntType()), new CompStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(2))), new PrintStatement(new VariableExpression("v"))));
        PrgState prg1 = new PrgState(ex1);
        prg1.init();
        IRepository repo1 = new MyRepository("file1.txt");
        repo1.addPrg(prg1);
        Controller controller1 = new Controller(repo1);

        //int a;int b; a=2+3*5; b=a+1; Print(b)
        IStatement ex2 = new CompStatement(new VarDeclStatement("a", new IntType()), new CompStatement(new VarDeclStatement("b", new IntType()), new CompStatement(new AssignmentStatement("a", new ArithmeticalExpression(new ValueExpression(new IntValue(2)), ArithmeticalOperator.ADD, new ArithmeticalExpression(new ValueExpression(new IntValue(3)), ArithmeticalOperator.MULTIPLY, new ValueExpression(new IntValue(5))))), new CompStatement(new AssignmentStatement("b", new ArithmeticalExpression(new VariableExpression("a"), ArithmeticalOperator.ADD, new ValueExpression(new IntValue(1)))), new PrintStatement(new VariableExpression("b"))))));

        PrgState prg2 = new PrgState(ex2);
        prg2.init();
        IRepository repo2 = new MyRepository("file2.txt");
        repo2.addPrg(prg2);
        Controller controller2 = new Controller(repo2);

        //bool a;int v; a=true; (If a Then v=2 Else v=3); Print(v)
        IStatement ex3 = new CompStatement(new VarDeclStatement("a", new BoolType()), new CompStatement(new VarDeclStatement("v", new IntType()), new CompStatement(new AssignmentStatement("a", new ValueExpression(new BoolValue(true))), new CompStatement(new IfStatement(new VariableExpression("a"), new AssignmentStatement("v", new ValueExpression(new IntValue(2))), new AssignmentStatement("v", new ValueExpression(new IntValue(3)))), new PrintStatement(new VariableExpression("v"))))));

        PrgState prg3 = new PrgState(ex3);
        prg3.init();
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
        prg4.init();
        IRepository repo4 = new MyRepository("file4.txt");
        repo4.addPrg(prg4);
        Controller controller4 = new Controller(repo4);


        IStatement ex5=new CompStatement(new VarDeclStatement("v", new RefType(new IntType())),
                new CompStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                        new CompStatement(new PrintStatement(new ReadHeapExpression(new VariableExpression("v"))),
                                new CompStatement(new HeapWritingStatement("v",new ValueExpression(new IntValue(30))),
                                        new PrintStatement(new ArithmeticalExpression(new ReadHeapExpression(new VariableExpression("v")), ArithmeticalOperator.ADD,new ValueExpression(new IntValue(5))))))));

        PrgState prg5=new PrgState(ex5);
        prg5.init();
        IRepository repo5=new MyRepository("file5.txt");
        repo5.addPrg(prg5);
        Controller controller5=new Controller(repo5);


        IStatement ex6=new CompStatement(new VarDeclStatement("v", new RefType(new IntType())),
                new CompStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                        new CompStatement(new VarDeclStatement("a", new RefType(new RefType(new IntType()))),
                                new CompStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                                        new CompStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(30))),
                                                new PrintStatement(new ReadHeapExpression(new ReadHeapExpression(new VariableExpression("a")))))))));

        PrgState prg6=new PrgState(ex6);
        prg6.init();
        IRepository repo6=new MyRepository("file6.txt");
        repo6.addPrg(prg6);
        Controller controller6=new Controller(repo6);


        IStatement ex7=new CompStatement(new VarDeclStatement("v", new RefType(new IntType())),
                new CompStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                        new CompStatement(new PrintStatement(new ReadHeapExpression(new VariableExpression("v"))),
                                new CompStatement(new HeapWritingStatement("v",new ValueExpression(new IntValue(30))),
                                        new CompStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(50))),
                                                new PrintStatement(new ArithmeticalExpression(new ReadHeapExpression(new VariableExpression("v")), ArithmeticalOperator.ADD,new ValueExpression(new IntValue(5)))))))));

        PrgState prg7=new PrgState(ex7);
        prg7.init();
        IRepository repo7=new MyRepository("file7.txt");
        repo7.addPrg(prg7);
        Controller controller7=new Controller(repo7);

        IStatement ex8=new CompStatement(new VarDeclStatement("v", new IntType()),
                new CompStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(4))),
                        new CompStatement(new WhileStatement(new RelationalExpression(new VariableExpression("v"), RelationalOperator.GRATER, new ValueExpression(new IntValue(0))), new CompStatement(new PrintStatement(new VariableExpression("v")), new AssignmentStatement("v", new ArithmeticalExpression(new VariableExpression("v"), ArithmeticalOperator.SUBTRACT, new ValueExpression(new IntValue(1)))))),
                                new PrintStatement(new VariableExpression("v")))));

        PrgState prg8=new PrgState(ex8);
        prg8.init();
        IRepository repo8=new MyRepository("file8.txt");
        repo8.addPrg(prg8);
        Controller controller8=new Controller(repo8);


        IStatement ex9 = new CompStatement(new VarDeclStatement("v", new IntType()),
                new CompStatement(new VarDeclStatement("a", new RefType(new IntType())),
                        new CompStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(10))),
                                new CompStatement(new HeapAllocationStatement("a", new ValueExpression(new IntValue(22))),
                                        new CompStatement(new ForkStatement(new CompStatement(new HeapWritingStatement("a", new ValueExpression(new IntValue(30))),
                                                                                 new CompStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(32))),
                                                                                         new CompStatement(new PrintStatement(new VariableExpression("v")),
                                                                                                 new PrintStatement(new ReadHeapExpression(new VariableExpression("a"))))))),
                                                new CompStatement(new PrintStatement(new VariableExpression("v")),
                                                        new PrintStatement(new ReadHeapExpression(new VariableExpression("a")))))))));

        PrgState prg9=new PrgState(ex9);
        prg9.init();
        IRepository repo9 =new MyRepository("file9.txt");
        repo9.addPrg(prg9);
        Controller controller9 = new Controller(repo9);


        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0", "exit"));
        menu.addCommand(new RunExample("1", ex1.toString(), controller1));
        menu.addCommand(new RunExample("2", ex2.toString(), controller2));
        menu.addCommand(new RunExample("3", ex3.toString(), controller3));
        menu.addCommand(new RunExample("4", ex4.toString(), controller4));
        menu.addCommand(new RunExample("5", ex5.toString(), controller5));
        menu.addCommand(new RunExample("6", ex6.toString(), controller6));
        menu.addCommand(new RunExample("7", ex7.toString(), controller7));
        menu.addCommand(new RunExample("8", ex8.toString(), controller8));
        menu.addCommand(new RunExample("9", ex9.toString(), controller9));
        menu.show();
    }
}
