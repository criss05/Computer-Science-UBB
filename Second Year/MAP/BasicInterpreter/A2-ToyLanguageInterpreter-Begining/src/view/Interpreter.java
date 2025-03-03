package view;

import exception.*;
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

import java.util.Scanner;

public class Interpreter {
    public static void run() throws ADTException, ExpressionException, RepoException, VariableAlreadyExists, StatementException {
        System.out.println("1.int v; v=2;Print(v)\n2.int a;int b; a=2+3*5;b=a+1;Print(b)\n3.bool a;int v; a=true; (If a Then v=2 Else v=3); Print(v)\n Choose an option:");
        Scanner scanner = new Scanner(System.in);
        String option = scanner.nextLine();
        switch(option){
            case "1":{
                //int v; v=2;Print(v)
                IStatement ex1 = new CompStatement(new VarDeclStatement("v", new IntType()), new CompStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(2))), new PrintStatement(new VariableExpression("v"))));
                PrgState prg1 = new PrgState(ex1);
                IRepository repo1 = new MyRepository();
                repo1.addPrg(prg1);
                Controller controller1 = new Controller(repo1);
                controller1.allSteps();
            }
            case "2":{
                //int a;int b; a=2+3*5;b=a+1;Print(b)
                IStatement ex2 = new CompStatement(new VarDeclStatement("a", new IntType()), new CompStatement(new VarDeclStatement("b", new IntType()), new CompStatement(new AssignmentStatement("a", new AritmeticalExpression(new ValueExpression(new IntValue(2)), AritmeticalOperator.ADD, new AritmeticalExpression(new ValueExpression(new IntValue(3)), AritmeticalOperator.MULTIPLY, new ValueExpression(new IntValue(5))))), new CompStatement(new AssignmentStatement("b", new AritmeticalExpression(new VariableExpression("a"), AritmeticalOperator.ADD, new ValueExpression(new IntValue(1)))), new PrintStatement(new VariableExpression("b"))))));
                PrgState prg2 = new PrgState(ex2);
                IRepository repo2 = new MyRepository();
                repo2.addPrg(prg2);
                Controller controller2 = new Controller(repo2);
                controller2.allSteps();
            }
            case "3":{
                //bool a;int v; a=true; (If a Then v=2 Else v=3); Print(v)
                IStatement ex3 = new CompStatement(new VarDeclStatement("a", new BoolType()), new CompStatement(new VarDeclStatement("v", new IntType()), new CompStatement(new AssignmentStatement("a", new ValueExpression(new BoolValue(true))), new CompStatement(new IfStatement(new VariableExpression("a"), new AssignmentStatement("v", new ValueExpression(new IntValue(2))), new AssignmentStatement("v", new ValueExpression(new IntValue(3)))), new PrintStatement(new VariableExpression("v"))))));
                PrgState prg3 = new PrgState(ex3);
                IRepository repo3 = new MyRepository();
                repo3.addPrg(prg3);
                Controller controller3 = new Controller(repo3);
                controller3.allSteps();
            }
        }
    }
}
