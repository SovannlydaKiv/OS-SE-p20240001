def fifo(ref_string, num_frames):
    frames = []
    queue = []  
    faults = 0
    print("=== FIFO ===")
    for ref in ref_string:
        if ref in frames:
            print(f"Ref {ref} | HIT   | frames: {frames}")
        else:
            faults += 1
            if len(frames) < num_frames:
                frames.append(ref)
                queue.append(ref)
                print(f"Ref {ref} | FAULT | frames: {frames}")
            else:
                victim = queue.pop(0)
                idx = frames.index(victim)
                frames[idx] = ref
                queue.append(ref)
                print(f"Ref {ref} | FAULT | frames: {frames}  (evicted {victim})")
    print(f"Total page faults (FIFO): {faults}\n")
    return faults


def lru(ref_string, num_frames):
    frames = []
    recency = []  
    faults = 0
    print("=== LRU ===")
    for ref in ref_string:
        if ref in frames:
            recency.remove(ref)
            recency.append(ref)
            print(f"Ref {ref} | HIT   | frames: {frames}")
        else:
            faults += 1
            if len(frames) < num_frames:
                frames.append(ref)
                recency.append(ref)
                print(f"Ref {ref} | FAULT | frames: {frames}")
            else:
                victim = recency.pop(0)
                idx = frames.index(victim)
                frames[idx] = ref
                recency.append(ref)
                print(f"Ref {ref} | FAULT | frames: {frames}  (evicted {victim})")
    print(f"Total page faults (LRU): {faults}\n")
    return faults


if __name__ == "__main__":
    full_string = [7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1]
    my_string = [1, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3]

    print("----- Full lecture string -----")
    f_full = fifo(full_string, 3)
    l_full = lru(full_string, 3)
    print(f"FIFO faults: {f_full} | LRU faults: {l_full}\n")

    print("----- My Part 2A string -----")
    f_mine = fifo(my_string, 3)
    l_mine = lru(my_string, 3)
    print(f"FIFO faults: {f_mine} | LRU faults: {l_mine}")