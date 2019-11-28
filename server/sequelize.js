const Sequelize = require("sequelize");
const BBQResourceModel = require("./models/bbq-resource");
const BBQIdModel = require("./models/bbq-id");
const chalk = require('chalk');
const isDevelopment = require("./environment").isDevelopment;


const sequelize = new Sequelize("bosp", "freelance", "prova123", {
  host: "localhost",
  dialect: "mysql",
  logging: false
});

sequelize
  .authenticate()
  .then(() => {
    console.log(chalk.bold.bgGreen.white("✓ Connection has been established successfully."));

  })
  .catch(err => {
    console.error("Unable to connect to the database:", err);
  });

const BBQid = BBQIdModel(sequelize, Sequelize);
const BBQresource = BBQResourceModel(sequelize, Sequelize);

BBQid.hasMany(BBQresource, {
  foreignKey: {
    name: "bbq_id",
    allowNull: false
  }
});

const resetDatabaseOnStart = isDevelopment;

sequelize
  .sync({
    force: resetDatabaseOnStart
  })
  .then(() => {
    console.log(chalk.bold.bgGreen.white("✓ Database and tables created!"));
  })
  .then(() => {
    initializeDatabase();
  });

/* Export the created models */
module.exports = {
  BBQid,
  BBQresource
};

function initializeDatabase() {
  if (isDevelopment) {
    console.log(chalk.bold.bgMagenta.white("=== Development mode! === "));
  }else {
    console.log(chalk.bold.bgGreen.white("=== Production mode! === "));
  }
}

