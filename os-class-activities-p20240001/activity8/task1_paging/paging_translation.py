P = 16
page_table = {0: 5, 1: 2, 2: 1, 4: 7, 6: 0, 7: 4}  

addresses = [20, 100, 48, 16, 127, 10]  

for la in addresses:
    page = la // P
    offset = la % P
    if page in page_table:
        frame = page_table[page]
        physical = frame * P + offset
        print(f"Logical {la} -> page {page}, offset {offset} -> frame {frame} -> physical {physical}")
    else:
        print(f"Logical {la} -> page {page} -> Page fault: page not in memory")