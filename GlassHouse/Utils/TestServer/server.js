const express = require('express');
const bodyParser = require('body-parser');
const fs = require('fs');

const app = express();
const port = process.argv[2] || 3000; // Utiliza el valor del primer argumento de la línea de comandos o 3000 como puerto predeterminado

// Validar que el puerto sea un valor numérico válido
if (isNaN(port) || port < 2000 || port > 65535) {
  console.error('El puerto especificado no es válido. Debe ser un número entre 2000 y 65535.');
  process.exit(1); // Salir del script con código de error 1
}

// Configurar el servidor para que acepte solicitudes JSON
app.use(bodyParser.json());

// Configurar el servidor para servir el archivo JSON
app.get('/data', (req, res) => {
  fs.readFile('data.json', 'utf8', (err, data) => {
    if (err) {
      console.error(err);
      res.status(500).send('Error interno del servidor');
      return;
    }

    res.send(data);
  });
});

// Configurar el servidor para que acepte solicitudes HTTP POST con el archivo JSON en el cuerpo de la solicitud.
app.post('/data', (req, res) => {
  const data = req.body;

  fs.writeFile('data.json', JSON.stringify(data), err => {
    if (err) {
      console.error(err);
      res.status(500).send('Error interno del servidor');
      return;
    }

    res.send('Servidor : Archivo guardado exitosamente');
  });
});

// Iniciar el servidor
app.listen(port, () => {
  console.log(`Servidor iniciado en http://localhost:${port}/data`);
});
