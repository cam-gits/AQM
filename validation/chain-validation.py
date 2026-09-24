import hashlib
import json

with open("aqm.jsonl", "r") as file:                                                                                        
    for line in file:
        record = json.loads(line)
        stored_hash = record.pop("hash")
        pre_hash = json.dumps(record, separators=(',', ':')).encode('utf-8')
        string_hash = hashlib.sha256(pre_hash).hexdigest()
        if stored_hash == string_hash:
            print("match")
        else: 
            print("fail")
        print("Stored Hash: ", stored_hash)
        print("Computed Hash: ", string_hash)