const express = require('express');

const personController = require('../controllers/person');

const router = express.Router();

router.get('/', personController.FindPersonDisplay);

module.exports = router;