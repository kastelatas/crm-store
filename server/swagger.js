const expressSwagger = require("express-swagger-generator");

const configureSwagger = (app) => {
  const expressSwaggerOptions = {
    swaggerDefinition: {
      info: {
        title: "API documentation",
        version: "1.0.0",
      },
      basePath: "/",
    },
    basedir: __dirname,
    files: ["./src/routes/*.js"],
  };

  expressSwagger(app)(expressSwaggerOptions);
};

module.exports = configureSwagger;
