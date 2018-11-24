const express = require('express');

const personController = require('../controllers/personApi');

const router = express.Router();

router.get('/:PersonID', personController.getPerson);
router.get('/:PersonID/children', personController.getChildren);
router.get('/:PersonID/parents', personController.getParents);
router.get('/firstName/:firstName', personController.getPersonByFirstName);

router.post('', personController.createPerson);
router.post('/relationship', personController.createRelationship);

module.exports = router;