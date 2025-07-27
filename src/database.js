import {Client} from "jsr:@db/postgres";
import * as path from "jsr:@std/path";

export var client = new Client({
    hostname: "localhost",
    port: 5432,
    user: "subnodal",
    password: "subnodal",
    database: "subnodal",
    tls: {
        enabled: false
    }
});

await client.connect();