const express = require('express')
const pg = require('pg')
const app = express()
const axios = require('axios')
const pgvector = require('pgvector/pg')

app.use(express.json());
app.use(express.urlencoded({extended: false}));

const db = new pg.Pool({
    host: 'aws-0-ap-northeast-2.pooler.supabase.com',
    user: 'postgres.bwixlrtfsaaargojatxx',
    password: '_____',
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
        });
    }
})

app.get('/', (req, res) => {
    res.send('Hello World!')
});

app.get('/new_emotion', async(req, res) => {
    var result = await axios.post('https://api.openai.com/v1/embeddings',
        {
            input: req.query.title,
            model: "text-embedding-3-small"
        },
        {
        headers: {
            'Content-Type': 'application/json',
            'Authorization': 'Bearer ' + '_____'
        }
    })

    var text = 'INSERT INTO "emotion-embeddings" (title, embedding) VALUES($1, $2)'
    var values = [req.query.title, pgvector.toSql(result.data.data[0].embedding)]
    await db.query(text, values)
    res.send('test')
});

app.get('/new_incident', async(req, res) => {
    var result = await axios.post('https://api.openai.com/v1/embeddings',
        {
            input: req.query.descriptor,
            model: "text-embedding-3-small"
        },
        {
        headers: {
            'Content-Type': 'application/json',
            'Authorization': 'Bearer ' + '_____'
        }
    })

    var text = 'SELECT 1 - (embedding <=> $1) AS similarity FROM "emotion-embeddings"'
    var values = [pgvector.toSql(result.data.data[0].embedding)]
    var similarity = await db.query(text, values);

    var similarity_arr = []
    for(var i = 0; i < similarity.rowCount; i++){
        similarity_arr.push(similarity.rows[i].similarity)
    }

    console.log(req.query.title)

    text = 'INSERT INTO "incident-embeddings" (title, similarity) VALUES ($1, $2)'
    values = [req.query.title, pgvector.toSql(similarity_arr)]
    db.query(text, values)

    res.send('test')
});

app.post('/closest_neighbor', async(req, res) => {
    var text = 'SELECT id, title, (similarity <=> $1) AS score FROM "incident-embeddings" ORDER BY score LIMIT 3'
    var values = [pgvector.toSql(req.body.user_state)]
    var rank = await db.query(text, values)
    res.send(rank);
});

app.get('/get_incidents', async(req, res) => {
    var text = 'SELECT title FROM "incident-embeddings"'
    var values = []
    var rank = await db.query(text, values)
    res.send(rank)
});