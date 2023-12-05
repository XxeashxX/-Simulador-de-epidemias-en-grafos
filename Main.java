import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;
public class Main {
    private static int length;
    private static int currentImageIndex = 0;
    private static JLabel label;
    public static void main(String[] args) {
        // Crear una nueva ventana
        JFrame frame = new JFrame("Ejecutar scripts");
        frame.setSize(1280, 720);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // Crear un panel para mostrar la imagen
        JPanel panel = new JPanel();
        frame.getContentPane().add(panel, BorderLayout.CENTER);

        // Crear campos de texto para ingresar los valores
        JTextField diasField = new JTextField(10);
        JTextField filasField = new JTextField(10);
        JTextField columnasField = new JTextField(10);
        JLabel diasLabel = new JLabel("Días:");
        JLabel filasLabel = new JLabel("Filas:");
        JLabel columnasLabel = new JLabel("Columnas:");
        panel.add(diasLabel);
        panel.add(diasField);
        panel.add(filasLabel);
        panel.add(filasField);
        panel.add(columnasLabel);
        panel.add(columnasField);
         // Crear botones para avanzar y retroceder (declaraciones agregadas)
         JButton nextButton = new JButton("Siguiente");
         nextButton.setVisible(false); // Inicialmente oculto
         JButton prevButton = new JButton("Anterior");
         prevButton.setVisible(false); // Inicialmente oculto
        // Crear un botón
        JButton button = new JButton("Ejecutar scripts");
        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // Ocultar el botón y los campos de texto
                panel.remove(button);
                panel.remove(diasLabel);
                panel.remove(diasField);    
                panel.remove(filasLabel);
                panel.remove(filasField);
                panel.remove(columnasLabel);
                panel.remove(columnasField);
                // Actualizar el panel para reflejar los cambios
                panel.revalidate();
                panel.repaint();
                try {
                    // Obtener los valores ingresados
                    String dias = diasField.getText();
                    String filas = filasField.getText();
                    String columnas = columnasField.getText();

                    // Ruta del archivo
                    String filePath = "C:/Users/edgar/OneDrive/Escritorio/taller 4/main.c";

                    // Leer el contenido del archivo
                    BufferedReader reader = new BufferedReader(new FileReader(filePath));
                    String line = reader.readLine();
                    StringBuilder content = new StringBuilder();
                    while (line != null) {
                        content.append(line).append(System.lineSeparator());
                        line = reader.readLine();
                    }
                    reader.close();

                    // Cambiar los valores
                    String newContent = content.toString()
                            .replace("int dias = 10;", "int dias = " + dias + ";")
                            .replace("int filas = 5;", "int filas = " + filas + ";")
                            .replace("int columnas = 5;", "int columnas = " + columnas + ";");

                    // Escribir el nuevo contenido en el archivo
                    BufferedWriter writer = new BufferedWriter(new FileWriter(filePath));
                    writer.write(newContent);
                    writer.close();

                    // Para compilar un programa en C
                    ProcessBuilder pbCompileC = new ProcessBuilder("gcc", "-o", "C:/Users/edgar/OneDrive/Escritorio/taller 4/output/main", "C:/Users/edgar/OneDrive/Escritorio/taller 4/output/main.c");
                    Process pCompile = pbCompileC.start();
                    pCompile.waitFor(); // Espera a que el proceso termine
                    System.out.println("se compilo C");

                    // Para ejecutar un programa en C
                    ProcessBuilder pbC = new ProcessBuilder("C:/Users/edgar/OneDrive/Escritorio/taller 4/output/main.exe");
                    Process p2 = pbC.start();
                    p2.waitFor(); // Espera a que el proceso termine
                    System.out.println("se ejecuto C");

                    // Para ejecutar un script de Python
                    String pythonScriptPath = "C:/Users/edgar/OneDrive/Escritorio/taller 4/grafo.py";
                    String[] cmd = new String[2];
                    cmd[0] = "C:/Users/edgar/AppData/Local/Microsoft/WindowsApps/PythonSoftwareFoundation.Python.3.11_qbz5n2kfra8p0/python.exe"; // Comprueba la ruta de tu intérprete de Python
                    cmd[1] = pythonScriptPath;
                    // Crea un proceso runtime para ejecutar el script de Python
                    Runtime rt = Runtime.getRuntime();
                    Process pr = rt.exec(cmd);
                    pr.waitFor(); // Espera a que el proceso termine
                    System.out.println("se ejecuto python");

                    // Captura y muestra los errores del script de Python
                    BufferedReader stdError = new BufferedReader(new InputStreamReader(pr.getErrorStream()));
                    String s = null;
                    while ((s = stdError.readLine()) != null) {
                        System.out.println(s);
                    }

                    // Crear un objeto File para representar el archivo
                    File file = new File("GripeSimulacion.csv");
                    try {
                        // Crear un objeto FileReader para leer el archivo
                        FileReader fileReader = new FileReader(file);
                        // Crear un objeto BufferedReader para leer el archivo línea por línea
                        BufferedReader bufferedReader = new BufferedReader(fileReader);
                        // leer primera línea para saber cantidad de días
                        String firstLine = bufferedReader.readLine();
                        // Cambio: Dividir la cadena en un arreglo de cadenas utilizando la coma como separador
                        String[] numbers = firstLine.split(",");
                        length = numbers.length;  // Actualizar la variable length correctamente
                        System.out.println("se cargo la cantidad de dias");
                        // Cerrar el BufferedReader y el FileReader
                        bufferedReader.close();
                        fileReader.close();
                    } catch (FileNotFoundException event) {
                        System.out.println("El archivo no se encontró");
                    } catch (IOException event) {
                        System.out.println("Error al leer el archivo");
                    }

                    // Hacer visible los botones de avanzar y retroceder
                    nextButton.setVisible(true);
                    prevButton.setVisible(true);
                    System.out.println("se cargaron boton next y prev");
                    // Cargar la primera imagen después de ejecutar el script
                    updateImage();

                    
                    System.out.println("se borraron los textos");
                } catch (IOException ex) {
                    ex.printStackTrace();
                } catch (InterruptedException ex) {
                    ex.printStackTrace();
                }
            }
        });
        
        panel.add(button, BorderLayout.SOUTH);

        // Crear un JLabel para mostrar la imagen
        label = new JLabel();
        panel.add(label, BorderLayout.CENTER);

        // Crear botones para avanzar y retroceder
        nextButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (currentImageIndex < length - 1) {
                    currentImageIndex++;
                    updateImage();
                }
            }
        });
        panel.add(nextButton, BorderLayout.EAST);

        prevButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (currentImageIndex > 0) {
                    currentImageIndex--;
                    updateImage();
                }
            }
        });
        panel.add(prevButton, BorderLayout.WEST);
        
        label.addMouseWheelListener(new MouseWheelListener() {
            @Override
            public void mouseWheelMoved(MouseWheelEvent e) {
                ImageIcon imageIcon = updateImage();
                int notches = e.getWheelRotation();
                if (notches < 0) {
                    // Zoom in
                    imageIcon = new ImageIcon(imageIcon.getImage().getScaledInstance(label.getWidth() + 10, label.getHeight() + 10, Image.SCALE_SMOOTH));
                } else {
                    // Zoom out
                    imageIcon = new ImageIcon(imageIcon.getImage().getScaledInstance(label.getWidth() - 10, label.getHeight() - 10, Image.SCALE_SMOOTH));
                }
                label.setIcon(imageIcon);
            }
        });
        
        // Hacer visible la ventana
        frame.setVisible(true);
        
    }
    
    private static ImageIcon updateImage() {

        String imagePath = String.format("C:/Users/edgar/OneDrive/Escritorio/taller 4/grafo_dia_%d.png", currentImageIndex + 1);
        ImageIcon imageIcon = new ImageIcon(imagePath);
        label.setIcon(imageIcon);
        return imageIcon;
    }
    
}
