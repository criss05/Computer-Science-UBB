package domain;

public class Author {
    private int id;
    private String name;
    private String documentList;
    private String moviesList;

    public Author(int id, String name, String documentList, String moviesList) {
        this.id = id;
        this.name = name;
        this.documentList = documentList;
        this.moviesList = moviesList;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getDocumentList() {
        return documentList;
    }

    public void setDocumentList(String documentList) {
        this.documentList = documentList;
    }

    public String getMoviesList() {
        return moviesList;
    }

    public void setMoviesList(String moviesList) {
        this.moviesList = moviesList;
    }
}
