const express = require('express');

const mainController = require('../controllers/main')

const router = express.Router();

router.get('', mainController.indexPage);

// 09 team
router.get('/09/team', mainController.week09Team);
router.post('/09/team/maths', mainController.week09TeamMaths);
router.post('/09/team/math_service', mainController.week09TeamMathService);

// 09 prove
router.get('/09/prove', mainController.week09Prove);
router.post('/09/prove/rate', mainController.wek09GetPostalRate);

module.exports = router;