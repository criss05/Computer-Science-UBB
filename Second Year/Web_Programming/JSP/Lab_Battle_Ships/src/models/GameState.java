package models;

import java.util.HashSet;
import java.util.Set;

public class GameState {
    private static final Set<String> players = new HashSet<>();

    public static synchronized boolean addPlayer(String username) {
        if (players.size() < 2){
            players.add(username);
            return true;
        }
        return false;
    }

    public static synchronized void removePlayer(String username) {
        players.remove(username);
    }

    public static synchronized boolean isReady() {
        return players.size() == 2;
    }
}
