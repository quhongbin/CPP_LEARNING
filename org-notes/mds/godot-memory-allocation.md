---
author: Hongbin Qu
date: \<2025-05-27 Tue\>
title: Godot Memory Allocation
---

# Godot Memory Allocation

Godot provides its own memory allocation system in `memory.h` and
`memory.cpp`. It wraps `malloc` and `calloc` with additional debugging
features.

## Memory::alloc~static~

This template function is the core allocator. It accepts a boolean
template parameter `p_ensure_zero`.

``` cpp
template <bool p_ensure_zero>
void *Memory::alloc_static(size_t p_bytes, bool p_pad_align)
```

## Key Features

1.  ****Zero-fill option**** --- If `p_ensure_zero` is `true`, it uses
    `calloc` (zero-initialized). Otherwise `malloc`.
2.  ****Padding / Alignment**** --- When `p_pad_align` is `true` (or
    always in debug mode), it adds `DATA_OFFSET` extra bytes before the
    actual data. This stores the allocation size.
3.  ****Size tracking**** --- The real size is written at `SIZE_OFFSET`
    bytes before the returned pointer. This helps detect buffer
    overflows.
4.  ****Profiling**** --- `GodotProfileAlloc` tracks memory usage
    statistics.
5.  ****Debug stats**** --- In debug mode, `_current_mem_usage` and
    `_max_mem_usage` track total memory.

## Memory Layout

\`\`\`

  --------------- --------------
  SIZE~OFFSET~    DATA~OFFSET~
  \[real size\]   \[padding\]
  --------------- --------------

\^ \^ \^ malloc ptr return ptr user starts here \`\`\`

## Related Notes

-   [C++ void\* Pointers](id:dae30869-f9e6-43e5-b188-661d59b714c4) ---
    alloc~static~ returns void\*
-   [C++ Templates](id:608ddcb6-9345-4cee-9aae-9dc1c2783338) --- the
    bool template parameter enables compile-time dispatch
-   [Copy Constructors](id:f5899ea2-320f-4845-8ed3-68b68ba1cdcd) ---
    Godot objects rely on proper copy semantics
-   [C++ Smart Pointers & Ref](id:1d07decd-4659-494a-835e-defca639a771)
    --- Ref works with Godot\'s memory system
-   [Reference Counting](id:d0d448fe-484e-49a2-9c29-aa7d34343744) ---
    many Godot objects are ref-counted
-   [C++ Memory Management](id:d90d89de-f807-4187-a9f7-a1501e9dcda5) ---
    parent topic
