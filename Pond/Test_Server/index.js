const express = require('express')
const pg = require('pg')
const app = express()
const axios = require('axios')
const pgvector = require('pgvector/pg')

app.use(express.json());
app.use(express.urlencoded({extended: false}));

const db = new pg.Pool({
    host: 'aws-0-ap-northeast-2.pooler.supabase.com',
    user: '___',
    password: '___',
    database: 'postgres', port: 6543, max: 5,
})

db.connect(err => {
    if(err){
        console.log('DB Connection Error: ' + err)
    }
    else{
        console.log('DB Connected')
        app.listen(8080, ()=>{
            console.log('Listening')
        })
    }
})

app.get('/get_incidents', async(req, res) => {
    var text = 'SELECT name FROM "incident-emotion-cosine-diff"'
    var values = []
    var result = await db.query(text, values)
    res.send(result)
})

app.get('/get_num_emotions', async(req, res) => {
    var text = 'SELECT COUNT(*) AS num FROM "emotion-embeddings"'
    var values = []
    var result = await db.query(text, values)
    res.send(result)
})

app.post('/add_incident', async(req, res) => {
    var result = await axios.post('https://api.openai.com/v1/embeddings',
        {
            input: req.body.description,
            model: "text-embedding-3-small"
        },
        {
        headers: {
            'Content-Type': 'application/json',
            'Authorization': 'Bearer ' + '___'
        }
    })
    var text = 'SELECT 1 - (embedding <=> $1) AS "cosinediff" FROM "emotion-embeddings"'
    var values = [pgvector.toSql(result.data.data[0].embedding)]
    var cosinediff = await db.query(text, values)
    var cosinediff_arr = []
    for(var i = 0; i < cosinediff.rowCount; i++){
        cosinediff_arr.push(cosinediff.rows[i].cosinediff)
    }
    text = 'INSERT INTO "incident-emotion-cosine-diff" (name, "cosine-diff", description) VALUES ($1, $2, $3)'
    values = [req.body.name, pgvector.toSql(cosinediff_arr), req.body.description]
    db.query(text, values)
    res.send('')
})

app.post('/preferred_incidents', async(req, res) => {
    var text = 'SELECT name, ("cosine-diff" <=> $1) AS similarity FROM "incident-emotion-cosine-diff" ORDER BY similarity DESC LIMIT 10'
    var values = [pgvector.toSql(req.body.user_state)]
    var rank = await db.query(text, values)
    res.send(rank)
})
