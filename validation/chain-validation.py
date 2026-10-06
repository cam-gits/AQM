import hashlib
import json

prevSeq = 0
firstRecord = True
issue = False

with open("aqm.jsonl", "r") as file:                                                                                        
    for line in file:
        record = json.loads(line)
        seq = record["seq"]
        prevRecord = record["prev"]
        stored_hash = record.pop("hash")
        pre_hash = json.dumps(record, separators=(',', ':')).encode('utf-8')
        string_hash = hashlib.sha256(pre_hash).hexdigest()

        if firstRecord == True:
            prevHash = record["prev"]
            firstRecord = False

        if stored_hash == string_hash:
            if seq == (prevSeq + 1) and prevHash == prevRecord:
                prevSeq += 1
                prevHash = stored_hash
            elif seq == 1:
                print(f"Chain restarts after line {prevSeq}")
                issue = True
                break
            else:
                print(f"Chain severed between lines {prevSeq} and {seq}")
                issue = True
                break
        else: 
            print(f"Hash mismatch at line {seq}")
            issue = True
            break

if issue == False:
    print(f"{seq} lines validated. No Tamper Evident.")