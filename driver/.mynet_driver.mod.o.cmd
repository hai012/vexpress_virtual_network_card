cmd_/home/ghj/work/vexpress/driver/mynet_driver.mod.o := /home/ghj/work/vexpress/tools/gcc-arm-10.3-2021.07-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-gcc -Wp,-MMD,/home/ghj/work/vexpress/driver/.mynet_driver.mod.o.d -nostdinc -I/home/ghj/work/vexpress/linux-6.1.15/arch/arm/include -I./arch/arm/include/generated -I/home/ghj/work/vexpress/linux-6.1.15/include -I./include -I/home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/uapi -I./arch/arm/include/generated/uapi -I/home/ghj/work/vexpress/linux-6.1.15/include/uapi -I./include/generated/uapi -include /home/ghj/work/vexpress/linux-6.1.15/include/linux/compiler-version.h -include /home/ghj/work/vexpress/linux-6.1.15/include/linux/kconfig.h -include /home/ghj/work/vexpress/linux-6.1.15/include/linux/compiler_types.h -D__KERNEL__ -mlittle-endian -fmacro-prefix-map=/home/ghj/work/vexpress/linux-6.1.15/= -Wall -Wundef -Werror=strict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -fshort-wchar -fno-PIE -Werror=implicit-function-declaration -Werror=implicit-int -Werror=return-type -Wno-format-security -std=gnu11 -fno-dwarf2-cfi-asm -mno-fdpic -fno-ipa-sra -mabi=aapcs-linux -mfpu=vfp -funwind-tables -mtp=cp15 -marm -Wa,-mno-warn-deprecated -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -fno-delete-null-pointer-checks -Wno-frame-address -Wno-format-truncation -Wno-format-overflow -Wno-address-of-packed-member -O2 -fno-allow-store-data-races -Wframe-larger-than=1024 -fstack-protector-strong -Wno-main -Wno-unused-but-set-variable -Wno-unused-const-variable -fomit-frame-pointer -fno-stack-clash-protection -Wdeclaration-after-statement -Wvla -Wno-pointer-sign -Wcast-function-type -Wno-stringop-truncation -Wno-stringop-overflow -Wno-restrict -Wno-maybe-uninitialized -Wno-alloc-size-larger-than -Wimplicit-fallthrough=5 -fno-strict-overflow -fno-stack-check -fconserve-stack -Werror=date-time -Werror=incompatible-pointer-types -Werror=designated-init -Wno-packed-not-aligned -g -fplugin=./scripts/gcc-plugins/arm_ssp_per_task_plugin.so -fplugin-arg-arm_ssp_per_task_plugin-offset=1272 -DMODULE -DKBUILD_BASENAME='"mynet_driver.mod"' -DKBUILD_MODNAME='"mynet_driver"' -D__KBUILD_MODNAME=kmod_mynet_driver -c -o /home/ghj/work/vexpress/driver/mynet_driver.mod.o /home/ghj/work/vexpress/driver/mynet_driver.mod.c

source_/home/ghj/work/vexpress/driver/mynet_driver.mod.o := /home/ghj/work/vexpress/driver/mynet_driver.mod.c

deps_/home/ghj/work/vexpress/driver/mynet_driver.mod.o := \
    $(wildcard include/config/MODULE_UNLOAD) \
    $(wildcard include/config/RETPOLINE) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/compiler-version.h \
    $(wildcard include/config/CC_VERSION_TEXT) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/kconfig.h \
    $(wildcard include/config/CPU_BIG_ENDIAN) \
    $(wildcard include/config/BOOGER) \
    $(wildcard include/config/FOO) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/compiler_types.h \
    $(wildcard include/config/DEBUG_INFO_BTF) \
    $(wildcard include/config/PAHOLE_HAS_BTF_TAG) \
    $(wildcard include/config/HAVE_ARCH_COMPILER_H) \
    $(wildcard include/config/CC_HAS_ASM_INLINE) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/compiler_attributes.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/compiler-gcc.h \
    $(wildcard include/config/ARCH_USE_BUILTIN_BSWAP) \
    $(wildcard include/config/SHADOW_CALL_STACK) \
    $(wildcard include/config/KCOV) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/module.h \
    $(wildcard include/config/MODULES) \
    $(wildcard include/config/SYSFS) \
    $(wildcard include/config/MODULES_TREE_LOOKUP) \
    $(wildcard include/config/LIVEPATCH) \
    $(wildcard include/config/STACKTRACE_BUILD_ID) \
    $(wildcard include/config/ARCH_USES_CFI_TRAPS) \
    $(wildcard include/config/MODULE_SIG) \
    $(wildcard include/config/ARCH_WANTS_MODULES_DATA_IN_VMALLOC) \
    $(wildcard include/config/GENERIC_BUG) \
    $(wildcard include/config/KALLSYMS) \
    $(wildcard include/config/SMP) \
    $(wildcard include/config/TRACEPOINTS) \
    $(wildcard include/config/TREE_SRCU) \
    $(wildcard include/config/BPF_EVENTS) \
    $(wildcard include/config/DEBUG_INFO_BTF_MODULES) \
    $(wildcard include/config/JUMP_LABEL) \
    $(wildcard include/config/TRACING) \
    $(wildcard include/config/EVENT_TRACING) \
    $(wildcard include/config/FTRACE_MCOUNT_RECORD) \
    $(wildcard include/config/KPROBES) \
    $(wildcard include/config/HAVE_STATIC_CALL_INLINE) \
    $(wildcard include/config/KUNIT) \
    $(wildcard include/config/PRINTK_INDEX) \
    $(wildcard include/config/CONSTRUCTORS) \
    $(wildcard include/config/FUNCTION_ERROR_INJECTION) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/list.h \
    $(wildcard include/config/DEBUG_LIST) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/container_of.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/build_bug.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/compiler.h \
    $(wildcard include/config/TRACE_BRANCH_PROFILING) \
    $(wildcard include/config/PROFILE_ALL_BRANCHES) \
    $(wildcard include/config/OBJTOOL) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/compiler_types.h \
  arch/arm/include/generated/asm/rwonce.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/rwonce.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/kasan-checks.h \
    $(wildcard include/config/KASAN_GENERIC) \
    $(wildcard include/config/KASAN_SW_TAGS) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/types.h \
    $(wildcard include/config/HAVE_UID16) \
    $(wildcard include/config/UID16) \
    $(wildcard include/config/ARCH_DMA_ADDR_T_64BIT) \
    $(wildcard include/config/PHYS_ADDR_T_64BIT) \
    $(wildcard include/config/64BIT) \
    $(wildcard include/config/ARCH_32BIT_USTAT_F_TINODE) \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/types.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/uapi/asm/types.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/int-ll64.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/asm-generic/int-ll64.h \
  arch/arm/include/generated/uapi/asm/bitsperlong.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/bitsperlong.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/asm-generic/bitsperlong.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/posix_types.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/stddef.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/stddef.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/uapi/asm/posix_types.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/asm-generic/posix_types.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/kcsan-checks.h \
    $(wildcard include/config/KCSAN) \
    $(wildcard include/config/KCSAN_WEAK_MEMORY) \
    $(wildcard include/config/KCSAN_IGNORE_ATOMICS) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/err.h \
  arch/arm/include/generated/uapi/asm/errno.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/asm-generic/errno.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/asm-generic/errno-base.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/poison.h \
    $(wildcard include/config/ILLEGAL_POINTER_VALUE) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/const.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/vdso/const.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/const.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/barrier.h \
    $(wildcard include/config/CPU_32v6K) \
    $(wildcard include/config/THUMB2_KERNEL) \
    $(wildcard include/config/CPU_XSC3) \
    $(wildcard include/config/CPU_FA526) \
    $(wildcard include/config/ARM_HEAVY_MB) \
    $(wildcard include/config/ARM_DMA_MEM_BUFFERABLE) \
    $(wildcard include/config/CPU_SPECTRE) \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/barrier.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/stat.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/uapi/asm/stat.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/stat.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/time.h \
    $(wildcard include/config/POSIX_TIMERS) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/cache.h \
    $(wildcard include/config/ARCH_HAS_CACHE_LINE_SIZE) \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/kernel.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/sysinfo.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/cache.h \
    $(wildcard include/config/ARM_L1_CACHE_SHIFT) \
    $(wildcard include/config/AEABI) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/math64.h \
    $(wildcard include/config/ARCH_SUPPORTS_INT128) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/math.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/div64.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/compiler.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/div64.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/log2.h \
    $(wildcard include/config/ARCH_HAS_ILOG2_U32) \
    $(wildcard include/config/ARCH_HAS_ILOG2_U64) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/bitops.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/bits.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/vdso/bits.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/typecheck.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/bitops/generic-non-atomic.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/bitops.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/irqflags.h \
    $(wildcard include/config/PROVE_LOCKING) \
    $(wildcard include/config/TRACE_IRQFLAGS) \
    $(wildcard include/config/PREEMPT_RT) \
    $(wildcard include/config/IRQSOFF_TRACER) \
    $(wildcard include/config/PREEMPT_TRACER) \
    $(wildcard include/config/DEBUG_IRQFLAGS) \
    $(wildcard include/config/TRACE_IRQFLAGS_SUPPORT) \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/irqflags.h \
    $(wildcard include/config/CPU_V7M) \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/ARM_THUMB) \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/uapi/asm/ptrace.h \
    $(wildcard include/config/CPU_ENDIAN_BE8) \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/hwcap.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/uapi/asm/hwcap.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/irqflags.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/percpu.h \
    $(wildcard include/config/CPU_V6) \
    $(wildcard include/config/ARM_HAS_GROUP_RELOCS) \
    $(wildcard include/config/ARM_MODULE_PLTS) \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/insn.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/percpu.h \
    $(wildcard include/config/DEBUG_PREEMPT) \
    $(wildcard include/config/HAVE_SETUP_PER_CPU_AREA) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/threads.h \
    $(wildcard include/config/NR_CPUS) \
    $(wildcard include/config/BASE_SMALL) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/percpu-defs.h \
    $(wildcard include/config/DEBUG_FORCE_WEAK_PER_CPU) \
    $(wildcard include/config/AMD_MEM_ENCRYPT) \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/bitops/non-atomic.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/bitops/non-instrumented-non-atomic.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/bitops/builtin-__fls.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/bitops/builtin-__ffs.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/bitops/builtin-fls.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/bitops/builtin-ffs.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/bitops/ffz.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/bitops/fls64.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/bitops/sched.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/bitops/hweight.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/bitops/arch_hweight.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/bitops/const_hweight.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/bitops/lock.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/atomic.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/atomic.h \
    $(wildcard include/config/GENERIC_ATOMIC64) \
    $(wildcard include/config/ARM_LPAE) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/prefetch.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/processor.h \
    $(wildcard include/config/HAVE_HW_BREAKPOINT) \
    $(wildcard include/config/BINFMT_ELF_FDPIC) \
    $(wildcard include/config/MMU) \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/hw_breakpoint.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/unified.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/vdso/processor.h \
    $(wildcard include/config/ARM_ERRATA_754327) \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/cmpxchg.h \
    $(wildcard include/config/CPU_SA1100) \
    $(wildcard include/config/CPU_SA110) \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/cmpxchg-local.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/atomic/atomic-arch-fallback.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/atomic/atomic-long.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/atomic/atomic-instrumented.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/instrumented.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/kmsan-checks.h \
    $(wildcard include/config/KMSAN) \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/bitops/instrumented-lock.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/bitops/le.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/uapi/asm/byteorder.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/byteorder/little_endian.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/byteorder/little_endian.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/swab.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/swab.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/swab.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/uapi/asm/swab.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/byteorder/generic.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/bitops/ext2-atomic-setbit.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/vdso/math64.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/time64.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/vdso/time64.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/time.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/time_types.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/time32.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/timex.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/timex.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/param.h \
  arch/arm/include/generated/uapi/asm/param.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/param.h \
    $(wildcard include/config/HZ) \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/asm-generic/param.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/timex.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/vdso/time32.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/vdso/time.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/uidgid.h \
    $(wildcard include/config/MULTIUSER) \
    $(wildcard include/config/USER_NS) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/highuid.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/buildid.h \
    $(wildcard include/config/CRASH_CORE) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/mm_types.h \
    $(wildcard include/config/HAVE_ALIGNED_STRUCT_PAGE) \
    $(wildcard include/config/MEMCG) \
    $(wildcard include/config/USERFAULTFD) \
    $(wildcard include/config/SWAP) \
    $(wildcard include/config/NUMA) \
    $(wildcard include/config/HAVE_ARCH_COMPAT_MMAP_BASES) \
    $(wildcard include/config/MEMBARRIER) \
    $(wildcard include/config/AIO) \
    $(wildcard include/config/MMU_NOTIFIER) \
    $(wildcard include/config/TRANSPARENT_HUGEPAGE) \
    $(wildcard include/config/NUMA_BALANCING) \
    $(wildcard include/config/ARCH_WANT_BATCHED_UNMAP_TLB_FLUSH) \
    $(wildcard include/config/HUGETLB_PAGE) \
    $(wildcard include/config/IOMMU_SVA) \
    $(wildcard include/config/KSM) \
    $(wildcard include/config/LRU_GEN) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/mm_types_task.h \
    $(wildcard include/config/SPLIT_PTLOCK_CPUS) \
    $(wildcard include/config/ARCH_ENABLE_SPLIT_PMD_PTLOCK) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/cpumask.h \
    $(wildcard include/config/FORCE_NR_CPUS) \
    $(wildcard include/config/HOTPLUG_CPU) \
    $(wildcard include/config/DEBUG_PER_CPU_MAPS) \
    $(wildcard include/config/CPUMASK_OFFSTACK) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/kernel.h \
    $(wildcard include/config/PREEMPT_VOLUNTARY_BUILD) \
    $(wildcard include/config/PREEMPT_DYNAMIC) \
    $(wildcard include/config/HAVE_PREEMPT_DYNAMIC_CALL) \
    $(wildcard include/config/HAVE_PREEMPT_DYNAMIC_KEY) \
    $(wildcard include/config/PREEMPT_) \
    $(wildcard include/config/DEBUG_ATOMIC_SLEEP) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/stdarg.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/align.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/limits.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/limits.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/vdso/limits.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/linkage.h \
    $(wildcard include/config/ARCH_USE_SYM_ANNOTATIONS) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/stringify.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/export.h \
    $(wildcard include/config/MODVERSIONS) \
    $(wildcard include/config/HAVE_ARCH_PREL32_RELOCATIONS) \
    $(wildcard include/config/TRIM_UNUSED_KSYMS) \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/linkage.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/kstrtox.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/minmax.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/panic.h \
    $(wildcard include/config/PANIC_TIMEOUT) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/printk.h \
    $(wildcard include/config/MESSAGE_LOGLEVEL_DEFAULT) \
    $(wildcard include/config/CONSOLE_LOGLEVEL_DEFAULT) \
    $(wildcard include/config/CONSOLE_LOGLEVEL_QUIET) \
    $(wildcard include/config/EARLY_PRINTK) \
    $(wildcard include/config/PRINTK) \
    $(wildcard include/config/DYNAMIC_DEBUG) \
    $(wildcard include/config/DYNAMIC_DEBUG_CORE) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/init.h \
    $(wildcard include/config/STRICT_KERNEL_RWX) \
    $(wildcard include/config/STRICT_MODULE_RWX) \
    $(wildcard include/config/LTO_CLANG) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/kern_levels.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/ratelimit_types.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/spinlock_types_raw.h \
    $(wildcard include/config/DEBUG_SPINLOCK) \
    $(wildcard include/config/DEBUG_LOCK_ALLOC) \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/spinlock_types.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/lockdep_types.h \
    $(wildcard include/config/PROVE_RAW_LOCK_NESTING) \
    $(wildcard include/config/LOCKDEP) \
    $(wildcard include/config/LOCK_STAT) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/once_lite.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/static_call_types.h \
    $(wildcard include/config/HAVE_STATIC_CALL) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/instruction_pointer.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/bitmap.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/find.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/string.h \
    $(wildcard include/config/BINARY_PRINTF) \
    $(wildcard include/config/FORTIFY_SOURCE) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/errno.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/errno.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/string.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/string.h \
    $(wildcard include/config/KASAN) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/bug.h \
    $(wildcard include/config/BUG_ON_DATA_CORRUPTION) \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/bug.h \
    $(wildcard include/config/DEBUG_BUGVERBOSE) \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/opcodes.h \
    $(wildcard include/config/CPU_ENDIAN_BE32) \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/bug.h \
    $(wildcard include/config/BUG) \
    $(wildcard include/config/GENERIC_BUG_RELATIVE_POINTERS) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/instrumentation.h \
    $(wildcard include/config/NOINSTR_VALIDATION) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/gfp_types.h \
    $(wildcard include/config/KASAN_HW_TAGS) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/numa.h \
    $(wildcard include/config/NODES_SHIFT) \
    $(wildcard include/config/NUMA_KEEP_MEMINFO) \
    $(wildcard include/config/HAVE_ARCH_NODE_DEV_GROUP) \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/page.h \
    $(wildcard include/config/CPU_COPY_V4WT) \
    $(wildcard include/config/CPU_COPY_V4WB) \
    $(wildcard include/config/CPU_COPY_FEROCEON) \
    $(wildcard include/config/CPU_COPY_FA) \
    $(wildcard include/config/CPU_XSCALE) \
    $(wildcard include/config/CPU_COPY_V6) \
    $(wildcard include/config/KUSER_HELPERS) \
    $(wildcard include/config/VMAP_STACK) \
    $(wildcard include/config/HAVE_ARCH_PFN_VALID) \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/glue.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/pgtable-2level-types.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/memory.h \
    $(wildcard include/config/NEED_MACH_MEMORY_H) \
    $(wildcard include/config/PAGE_OFFSET) \
    $(wildcard include/config/HIGHMEM) \
    $(wildcard include/config/DRAM_BASE) \
    $(wildcard include/config/DRAM_SIZE) \
    $(wildcard include/config/XIP_KERNEL) \
    $(wildcard include/config/HAVE_TCM) \
    $(wildcard include/config/ARM_PATCH_PHYS_VIRT) \
    $(wildcard include/config/PHYS_OFFSET) \
    $(wildcard include/config/DEBUG_VIRTUAL) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/sizes.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/kasan_def.h \
    $(wildcard include/config/KASAN_SHADOW_OFFSET) \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/memory_model.h \
    $(wildcard include/config/FLATMEM) \
    $(wildcard include/config/SPARSEMEM_VMEMMAP) \
    $(wildcard include/config/SPARSEMEM) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/pfn.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/getorder.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/auxvec.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/auxvec.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/auxvec.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/uapi/asm/auxvec.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/kref.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/spinlock.h \
    $(wildcard include/config/PREEMPTION) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/preempt.h \
    $(wildcard include/config/PREEMPT_COUNT) \
    $(wildcard include/config/TRACE_PREEMPT_TOGGLE) \
    $(wildcard include/config/PREEMPT_NOTIFIERS) \
  arch/arm/include/generated/asm/preempt.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/preempt.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/thread_info.h \
    $(wildcard include/config/THREAD_INFO_IN_TASK) \
    $(wildcard include/config/GENERIC_ENTRY) \
    $(wildcard include/config/HAVE_ARCH_WITHIN_STACK_FRAMES) \
    $(wildcard include/config/HARDENED_USERCOPY) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/restart_block.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/current.h \
    $(wildcard include/config/CURRENT_POINTER_IN_TPIDRURO) \
    $(wildcard include/config/CC_IS_CLANG) \
    $(wildcard include/config/CLANG_VERSION) \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/thread_info.h \
    $(wildcard include/config/ARM_THUMBEE) \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/fpstate.h \
    $(wildcard include/config/VFPv3) \
    $(wildcard include/config/IWMMXT) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/bottom_half.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/lockdep.h \
    $(wildcard include/config/DEBUG_LOCKING_API_SELFTESTS) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/smp.h \
    $(wildcard include/config/UP_LATE_INIT) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/smp_types.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/llist.h \
    $(wildcard include/config/ARCH_HAVE_NMI_SAFE_CMPXCHG) \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/smp.h \
  arch/arm/include/generated/asm/mmiowb.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/mmiowb.h \
    $(wildcard include/config/MMIOWB) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/spinlock_types.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/rwlock_types.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/spinlock.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/rwlock.h \
    $(wildcard include/config/PREEMPT) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/spinlock_api_smp.h \
    $(wildcard include/config/INLINE_SPIN_LOCK) \
    $(wildcard include/config/INLINE_SPIN_LOCK_BH) \
    $(wildcard include/config/INLINE_SPIN_LOCK_IRQ) \
    $(wildcard include/config/INLINE_SPIN_LOCK_IRQSAVE) \
    $(wildcard include/config/INLINE_SPIN_TRYLOCK) \
    $(wildcard include/config/INLINE_SPIN_TRYLOCK_BH) \
    $(wildcard include/config/UNINLINE_SPIN_UNLOCK) \
    $(wildcard include/config/INLINE_SPIN_UNLOCK_BH) \
    $(wildcard include/config/INLINE_SPIN_UNLOCK_IRQ) \
    $(wildcard include/config/INLINE_SPIN_UNLOCK_IRQRESTORE) \
    $(wildcard include/config/GENERIC_LOCKBREAK) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/rwlock_api_smp.h \
    $(wildcard include/config/INLINE_READ_LOCK) \
    $(wildcard include/config/INLINE_WRITE_LOCK) \
    $(wildcard include/config/INLINE_READ_LOCK_BH) \
    $(wildcard include/config/INLINE_WRITE_LOCK_BH) \
    $(wildcard include/config/INLINE_READ_LOCK_IRQ) \
    $(wildcard include/config/INLINE_WRITE_LOCK_IRQ) \
    $(wildcard include/config/INLINE_READ_LOCK_IRQSAVE) \
    $(wildcard include/config/INLINE_WRITE_LOCK_IRQSAVE) \
    $(wildcard include/config/INLINE_READ_TRYLOCK) \
    $(wildcard include/config/INLINE_WRITE_TRYLOCK) \
    $(wildcard include/config/INLINE_READ_UNLOCK) \
    $(wildcard include/config/INLINE_WRITE_UNLOCK) \
    $(wildcard include/config/INLINE_READ_UNLOCK_BH) \
    $(wildcard include/config/INLINE_WRITE_UNLOCK_BH) \
    $(wildcard include/config/INLINE_READ_UNLOCK_IRQ) \
    $(wildcard include/config/INLINE_WRITE_UNLOCK_IRQ) \
    $(wildcard include/config/INLINE_READ_UNLOCK_IRQRESTORE) \
    $(wildcard include/config/INLINE_WRITE_UNLOCK_IRQRESTORE) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/refcount.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/rbtree.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/rbtree_types.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/rcupdate.h \
    $(wildcard include/config/PREEMPT_RCU) \
    $(wildcard include/config/TINY_RCU) \
    $(wildcard include/config/RCU_STRICT_GRACE_PERIOD) \
    $(wildcard include/config/TASKS_RCU_GENERIC) \
    $(wildcard include/config/RCU_STALL_COMMON) \
    $(wildcard include/config/NO_HZ_FULL) \
    $(wildcard include/config/KVM_XFER_TO_GUEST_WORK) \
    $(wildcard include/config/RCU_NOCB_CPU) \
    $(wildcard include/config/TASKS_RCU) \
    $(wildcard include/config/TASKS_TRACE_RCU) \
    $(wildcard include/config/TASKS_RUDE_RCU) \
    $(wildcard include/config/TREE_RCU) \
    $(wildcard include/config/DEBUG_OBJECTS_RCU_HEAD) \
    $(wildcard include/config/PROVE_RCU) \
    $(wildcard include/config/ARCH_WEAK_RELEASE_ACQUIRE) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/context_tracking_irq.h \
    $(wildcard include/config/CONTEXT_TRACKING_IDLE) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/rcutree.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/maple_tree.h \
    $(wildcard include/config/MAPLE_RCU_DISABLED) \
    $(wildcard include/config/DEBUG_MAPLE_TREE_VERBOSE) \
    $(wildcard include/config/DEBUG_MAPLE_TREE) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/rwsem.h \
    $(wildcard include/config/RWSEM_SPIN_ON_OWNER) \
    $(wildcard include/config/DEBUG_RWSEMS) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/osq_lock.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/completion.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/swait.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/wait.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/wait.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/uprobes.h \
    $(wildcard include/config/UPROBES) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/page-flags-layout.h \
  include/generated/bounds.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/workqueue.h \
    $(wildcard include/config/DEBUG_OBJECTS_WORK) \
    $(wildcard include/config/FREEZER) \
    $(wildcard include/config/WQ_WATCHDOG) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/timer.h \
    $(wildcard include/config/DEBUG_OBJECTS_TIMERS) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/ktime.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/jiffies.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/vdso/jiffies.h \
  include/generated/timeconst.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/vdso/ktime.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/timekeeping.h \
    $(wildcard include/config/GENERIC_CMOS_UPDATE) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/clocksource_ids.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/debugobjects.h \
    $(wildcard include/config/DEBUG_OBJECTS) \
    $(wildcard include/config/DEBUG_OBJECTS_FREE) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/seqlock.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/mutex.h \
    $(wildcard include/config/MUTEX_SPIN_ON_OWNER) \
    $(wildcard include/config/DEBUG_MUTEXES) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/debug_locks.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/mmu.h \
    $(wildcard include/config/CPU_HAS_ASID) \
    $(wildcard include/config/VDSO) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/kmod.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/umh.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/gfp.h \
    $(wildcard include/config/ZONE_DMA) \
    $(wildcard include/config/ZONE_DMA32) \
    $(wildcard include/config/ZONE_DEVICE) \
    $(wildcard include/config/PM_SLEEP) \
    $(wildcard include/config/CONTIG_ALLOC) \
    $(wildcard include/config/CMA) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/mmzone.h \
    $(wildcard include/config/ARCH_FORCE_MAX_ORDER) \
    $(wildcard include/config/MEMORY_ISOLATION) \
    $(wildcard include/config/ZSMALLOC) \
    $(wildcard include/config/LRU_GEN_STATS) \
    $(wildcard include/config/MEMORY_HOTPLUG) \
    $(wildcard include/config/COMPACTION) \
    $(wildcard include/config/PAGE_EXTENSION) \
    $(wildcard include/config/DEFERRED_STRUCT_PAGE_INIT) \
    $(wildcard include/config/HAVE_MEMORYLESS_NODES) \
    $(wildcard include/config/SPARSEMEM_EXTREME) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/nodemask.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/random.h \
    $(wildcard include/config/VMGENID) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/once.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/jump_label.h \
    $(wildcard include/config/HAVE_ARCH_JUMP_LABEL_RELATIVE) \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/random.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/ioctl.h \
  arch/arm/include/generated/uapi/asm/ioctl.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/ioctl.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/asm-generic/ioctl.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/irqnr.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/irqnr.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/prandom.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/percpu.h \
    $(wildcard include/config/NEED_PER_CPU_EMBED_FIRST_CHUNK) \
    $(wildcard include/config/NEED_PER_CPU_PAGE_FIRST_CHUNK) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/mmdebug.h \
    $(wildcard include/config/DEBUG_VM) \
    $(wildcard include/config/DEBUG_VM_IRQSOFF) \
    $(wildcard include/config/DEBUG_VM_PGFLAGS) \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/archrandom.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/archrandom.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/pageblock-flags.h \
    $(wildcard include/config/HUGETLB_PAGE_SIZE_VARIABLE) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/page-flags.h \
    $(wildcard include/config/ARCH_USES_PG_UNCACHED) \
    $(wildcard include/config/MEMORY_FAILURE) \
    $(wildcard include/config/PAGE_IDLE_FLAG) \
    $(wildcard include/config/HUGETLB_PAGE_OPTIMIZE_VMEMMAP) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/local_lock.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/local_lock_internal.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/memory_hotplug.h \
    $(wildcard include/config/HAVE_ARCH_NODEDATA_EXTENSION) \
    $(wildcard include/config/ARCH_HAS_ADD_PAGES) \
    $(wildcard include/config/MEMORY_HOTREMOVE) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/notifier.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/srcu.h \
    $(wildcard include/config/TINY_SRCU) \
    $(wildcard include/config/SRCU) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/rcu_segcblist.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/srcutree.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/rcu_node_tree.h \
    $(wildcard include/config/RCU_FANOUT) \
    $(wildcard include/config/RCU_FANOUT_LEAF) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/topology.h \
    $(wildcard include/config/USE_PERCPU_NUMA_NODE_ID) \
    $(wildcard include/config/SCHED_SMT) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/arch_topology.h \
    $(wildcard include/config/ACPI_CPPC_LIB) \
    $(wildcard include/config/GENERIC_ARCH_TOPOLOGY) \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/topology.h \
    $(wildcard include/config/ARM_CPU_TOPOLOGY) \
    $(wildcard include/config/BL_SWITCHER) \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/topology.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/sysctl.h \
    $(wildcard include/config/SYSCTL) \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/sysctl.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/elf.h \
    $(wildcard include/config/ARCH_USE_GNU_PROPERTY) \
    $(wildcard include/config/ARCH_HAVE_ELF_PROT) \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/elf.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/vdso_datapage.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/vdso/datapage.h \
    $(wildcard include/config/ARCH_HAS_VDSO_DATA) \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/asm-generic/errno-base.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/vdso/clocksource.h \
    $(wildcard include/config/GENERIC_GETTIMEOFDAY) \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/vdso/clocksource.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/vdso/processor.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/vdso/gettimeofday.h \
    $(wildcard include/config/ARM_ARCH_TIMER) \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/unistd.h \
    $(wildcard include/config/OABI_COMPAT) \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/uapi/asm/unistd.h \
  arch/arm/include/generated/uapi/asm/unistd-eabi.h \
  arch/arm/include/generated/asm/unistd-nr.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/vdso/cp15.h \
    $(wildcard include/config/CPU_CP15) \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/user.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/elf.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/elf-em.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/kobject.h \
    $(wildcard include/config/UEVENT_HELPER) \
    $(wildcard include/config/DEBUG_KOBJECT_RELEASE) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/sysfs.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/kernfs.h \
    $(wildcard include/config/KERNFS) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/idr.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/radix-tree.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/xarray.h \
    $(wildcard include/config/XARRAY_MULTI) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/kconfig.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/sched/mm.h \
    $(wildcard include/config/ARCH_HAS_MEMBARRIER_CALLBACKS) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/sched.h \
    $(wildcard include/config/VIRT_CPU_ACCOUNTING_NATIVE) \
    $(wildcard include/config/SCHED_INFO) \
    $(wildcard include/config/SCHEDSTATS) \
    $(wildcard include/config/SCHED_CORE) \
    $(wildcard include/config/FAIR_GROUP_SCHED) \
    $(wildcard include/config/RT_GROUP_SCHED) \
    $(wildcard include/config/RT_MUTEXES) \
    $(wildcard include/config/UCLAMP_TASK) \
    $(wildcard include/config/UCLAMP_BUCKETS_COUNT) \
    $(wildcard include/config/KMAP_LOCAL) \
    $(wildcard include/config/CGROUP_SCHED) \
    $(wildcard include/config/BLK_DEV_IO_TRACE) \
    $(wildcard include/config/PSI) \
    $(wildcard include/config/COMPAT_BRK) \
    $(wildcard include/config/CGROUPS) \
    $(wildcard include/config/BLK_CGROUP) \
    $(wildcard include/config/PAGE_OWNER) \
    $(wildcard include/config/EVENTFD) \
    $(wildcard include/config/CPU_SUP_INTEL) \
    $(wildcard include/config/TASK_DELAY_ACCT) \
    $(wildcard include/config/STACKPROTECTOR) \
    $(wildcard include/config/ARCH_HAS_SCALED_CPUTIME) \
    $(wildcard include/config/VIRT_CPU_ACCOUNTING_GEN) \
    $(wildcard include/config/POSIX_CPUTIMERS) \
    $(wildcard include/config/POSIX_CPU_TIMERS_TASK_WORK) \
    $(wildcard include/config/KEYS) \
    $(wildcard include/config/SYSVIPC) \
    $(wildcard include/config/DETECT_HUNG_TASK) \
    $(wildcard include/config/IO_URING) \
    $(wildcard include/config/AUDIT) \
    $(wildcard include/config/AUDITSYSCALL) \
    $(wildcard include/config/UBSAN) \
    $(wildcard include/config/UBSAN_TRAP) \
    $(wildcard include/config/TASK_XACCT) \
    $(wildcard include/config/CPUSETS) \
    $(wildcard include/config/X86_CPU_RESCTRL) \
    $(wildcard include/config/FUTEX) \
    $(wildcard include/config/COMPAT) \
    $(wildcard include/config/PERF_EVENTS) \
    $(wildcard include/config/RSEQ) \
    $(wildcard include/config/FAULT_INJECTION) \
    $(wildcard include/config/LATENCYTOP) \
    $(wildcard include/config/FUNCTION_GRAPH_TRACER) \
    $(wildcard include/config/BCACHE) \
    $(wildcard include/config/SECURITY) \
    $(wildcard include/config/BPF_SYSCALL) \
    $(wildcard include/config/GCC_PLUGIN_STACKLEAK) \
    $(wildcard include/config/X86_MCE) \
    $(wildcard include/config/KRETPROBES) \
    $(wildcard include/config/RETHOOK) \
    $(wildcard include/config/ARCH_HAS_PARANOID_L1D_FLUSH) \
    $(wildcard include/config/RV) \
    $(wildcard include/config/ARCH_TASK_STRUCT_ON_STACK) \
    $(wildcard include/config/PREEMPT_NONE) \
    $(wildcard include/config/PREEMPT_VOLUNTARY) \
    $(wildcard include/config/DEBUG_RSEQ) \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/sched.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/pid.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/rculist.h \
    $(wildcard include/config/PROVE_RCU_LIST) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/sem.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/sem.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/ipc.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/rhashtable-types.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/ipc.h \
  arch/arm/include/generated/uapi/asm/ipcbuf.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/asm-generic/ipcbuf.h \
  arch/arm/include/generated/uapi/asm/sembuf.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/asm-generic/sembuf.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/shm.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/shm.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/asm-generic/hugetlb_encode.h \
  arch/arm/include/generated/uapi/asm/shmbuf.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/asm-generic/shmbuf.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/shmparam.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/kmsan_types.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/plist.h \
    $(wildcard include/config/DEBUG_PLIST) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/hrtimer.h \
    $(wildcard include/config/HIGH_RES_TIMERS) \
    $(wildcard include/config/TIME_LOW_RES) \
    $(wildcard include/config/TIMERFD) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/hrtimer_defs.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/timerqueue.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/seccomp.h \
    $(wildcard include/config/SECCOMP) \
    $(wildcard include/config/HAVE_ARCH_SECCOMP_FILTER) \
    $(wildcard include/config/SECCOMP_FILTER) \
    $(wildcard include/config/CHECKPOINT_RESTORE) \
    $(wildcard include/config/SECCOMP_CACHE_DEBUG) \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/seccomp.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/seccomp.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/seccomp.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/unistd.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/resource.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/resource.h \
  arch/arm/include/generated/uapi/asm/resource.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/resource.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/asm-generic/resource.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/latencytop.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/sched/prio.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/sched/types.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/signal_types.h \
    $(wildcard include/config/OLD_SIGACTION) \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/signal.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/signal.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/uapi/asm/signal.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/asm-generic/signal-defs.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/uapi/asm/sigcontext.h \
  arch/arm/include/generated/uapi/asm/siginfo.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/asm-generic/siginfo.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/syscall_user_dispatch.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/task_io_accounting.h \
    $(wildcard include/config/TASK_IO_ACCOUNTING) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/posix-timers.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/alarmtimer.h \
    $(wildcard include/config/RTC_CLASS) \
  /home/ghj/work/vexpress/linux-6.1.15/include/uapi/linux/rseq.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/kcsan.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/rv.h \
    $(wildcard include/config/RV_REACTORS) \
  arch/arm/include/generated/asm/kmap_size.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/kmap_size.h \
    $(wildcard include/config/DEBUG_KMAP_LOCAL) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/sync_core.h \
    $(wildcard include/config/ARCH_HAS_SYNC_CORE_BEFORE_USERMODE) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/ioasid.h \
    $(wildcard include/config/IOASID) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/kobject_ns.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/moduleparam.h \
    $(wildcard include/config/ALPHA) \
    $(wildcard include/config/IA64) \
    $(wildcard include/config/PPC64) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/rbtree_latch.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/error-injection.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/error-injection.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/tracepoint-defs.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/static_key.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/module.h \
    $(wildcard include/config/ARM_UNWIND) \
  /home/ghj/work/vexpress/linux-6.1.15/include/asm-generic/module.h \
    $(wildcard include/config/HAVE_MOD_ARCH_SPECIFIC) \
    $(wildcard include/config/MODULES_USE_ELF_REL) \
    $(wildcard include/config/MODULES_USE_ELF_RELA) \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/unwind.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/build-salt.h \
    $(wildcard include/config/BUILD_SALT) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/elfnote.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/elfnote-lto.h \
    $(wildcard include/config/LTO) \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/export-internal.h \
  /home/ghj/work/vexpress/linux-6.1.15/include/linux/vermagic.h \
    $(wildcard include/config/PREEMPT_BUILD) \
  include/generated/utsrelease.h \
  /home/ghj/work/vexpress/linux-6.1.15/arch/arm/include/asm/vermagic.h \

/home/ghj/work/vexpress/driver/mynet_driver.mod.o: $(deps_/home/ghj/work/vexpress/driver/mynet_driver.mod.o)

$(deps_/home/ghj/work/vexpress/driver/mynet_driver.mod.o):
