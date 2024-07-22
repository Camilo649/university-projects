package app.utils;

public final class DirectoryPaths {
    
    private String dataPath;

    public DirectoryPaths() throws IllegalArgumentException {
        dataPath = System.getenv("APP_HOME");
        if (dataPath != null) {
            dataPath += "/namedentitiescount/data";
        }
        else {
            throw new IllegalArgumentException("APP_HOME environment variable is not set appropriately.");
        }
    }

    public String getDataPath() {
        return dataPath;
    }
}
