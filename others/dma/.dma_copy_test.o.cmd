cmd_/mnt/samba/petalinux/zcu102/work/dma/dma_copy_test.o := gcc -Wp,-MMD,/mnt/samba/petalinux/zcu102/work/dma/.dma_copy_test.o.d  -nostdinc -isystem /usr/lib/gcc/aarch64-linux-gnu/9/include -I/root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include -I./arch/arm64/include/generated -I/root/petalinux/linux-xlnx-xilinx-v2021.1/include -I./include -I/root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/uapi -I./arch/arm64/include/generated/uapi -I/root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi -I./include/generated/uapi -include /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/kconfig.h -include /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/compiler_types.h -D__KERNEL__ -mlittle-endian -DCC_USING_PATCHABLE_FUNCTION_ENTRY -DKASAN_SHADOW_SCALE_SHIFT=3 -fmacro-prefix-map=/root/petalinux/linux-xlnx-xilinx-v2021.1/= -Wall -Wundef -Werror=strict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -fshort-wchar -fno-PIE -Werror=implicit-function-declaration -Werror=implicit-int -Werror=return-type -Wno-format-security -std=gnu89 -mgeneral-regs-only -DCONFIG_CC_HAS_K_CONSTRAINT=1 -Wno-psabi -mabi=lp64 -fno-asynchronous-unwind-tables -fno-unwind-tables -mbranch-protection=pac-ret+leaf -Wa,-march=armv8.4-a -DARM64_ASM_ARCH='"armv8.4-a"' -DKASAN_SHADOW_SCALE_SHIFT=3 -fno-delete-null-pointer-checks -Wno-frame-address -Wno-format-truncation -Wno-format-overflow -Wno-address-of-packed-member -O2 --param=allow-store-data-races=0 -Wframe-larger-than=2048 -fstack-protector-strong -Wno-unused-but-set-variable -Wimplicit-fallthrough -Wno-unused-const-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -fpatchable-function-entry=2 -Wdeclaration-after-statement -Wvla -Wno-pointer-sign -Wno-stringop-truncation -Wno-array-bounds -Wno-stringop-overflow -Wno-restrict -Wno-maybe-uninitialized -fno-strict-overflow -fno-stack-check -fconserve-stack -Werror=date-time -Werror=incompatible-pointer-types -Werror=designated-init -Wno-packed-not-aligned -mstack-protector-guard=sysreg -mstack-protector-guard-reg=sp_el0 -mstack-protector-guard-offset=984  -DMODULE  -DKBUILD_BASENAME='"dma_copy_test"' -DKBUILD_MODNAME='"dma_copy_test"' -c -o /mnt/samba/petalinux/zcu102/work/dma/dma_copy_test.o /mnt/samba/petalinux/zcu102/work/dma/dma_copy_test.c

source_/mnt/samba/petalinux/zcu102/work/dma/dma_copy_test.o := /mnt/samba/petalinux/zcu102/work/dma/dma_copy_test.c

deps_/mnt/samba/petalinux/zcu102/work/dma/dma_copy_test.o := \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/kconfig.h \
    $(wildcard include/config/cc/version/text.h) \
    $(wildcard include/config/cpu/big/endian.h) \
    $(wildcard include/config/booger.h) \
    $(wildcard include/config/foo.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/compiler_types.h \
    $(wildcard include/config/have/arch/compiler/h.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/cc/has/asm/inline.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/compiler_attributes.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/compiler-gcc.h \
    $(wildcard include/config/retpoline.h) \
    $(wildcard include/config/arch/use/builtin/bswap.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/compiler.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/dmaengine.h \
    $(wildcard include/config/debug/fs.h) \
    $(wildcard include/config/dma/engine/raid.h) \
    $(wildcard include/config/async/tx/enable/channel/switch.h) \
    $(wildcard include/config/dma/engine.h) \
    $(wildcard include/config/rapidio/dma/engine.h) \
    $(wildcard include/config/async/tx/dma.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/device.h \
    $(wildcard include/config/debug/devres.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/energy/model.h) \
    $(wildcard include/config/generic/msi/irq/domain.h) \
    $(wildcard include/config/pinctrl.h) \
    $(wildcard include/config/generic/msi/irq.h) \
    $(wildcard include/config/dma/ops.h) \
    $(wildcard include/config/dma/declare/coherent.h) \
    $(wildcard include/config/dma/cma.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/arch/has/sync/dma/for/device.h) \
    $(wildcard include/config/arch/has/sync/dma/for/cpu.h) \
    $(wildcard include/config/arch/has/sync/dma/for/cpu/all.h) \
    $(wildcard include/config/dma/ops/bypass.h) \
    $(wildcard include/config/srcu.h) \
    $(wildcard include/config/pm/sleep.h) \
    $(wildcard include/config/of.h) \
    $(wildcard include/config/devtmpfs.h) \
    $(wildcard include/config/sysfs/deprecated.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/dev_printk.h \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
    $(wildcard include/config/dynamic/debug/core.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/compiler.h \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/stack/validation.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/compiler_types.h \
  arch/arm64/include/generated/asm/rwonce.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/rwonce.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/kasan-checks.h \
    $(wildcard include/config/kasan.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/types.h \
    $(wildcard include/config/have/uid16.h) \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/types.h \
  arch/arm64/include/generated/uapi/asm/types.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/asm-generic/types.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/int-ll64.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/asm-generic/int-ll64.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/uapi/asm/bitsperlong.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/bitsperlong.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/asm-generic/bitsperlong.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/posix_types.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/stddef.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/stddef.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/uapi/asm/posix_types.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/asm-generic/posix_types.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/kcsan-checks.h \
    $(wildcard include/config/kcsan.h) \
    $(wildcard include/config/kcsan/ignore/atomics.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/ratelimit.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/ratelimit_types.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/bits.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/const.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/vdso/const.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/const.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/vdso/bits.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/build_bug.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/param.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/uapi/asm/param.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/param.h \
    $(wildcard include/config/hz.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/asm-generic/param.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/spinlock_types.h \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/spinlock_types.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/qspinlock_types.h \
    $(wildcard include/config/nr/cpus.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/qrwlock_types.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/uapi/asm/byteorder.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/byteorder/little_endian.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/byteorder/little_endian.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/swab.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/swab.h \
  arch/arm64/include/generated/uapi/asm/swab.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/asm-generic/swab.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/byteorder/generic.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/lockdep_types.h \
    $(wildcard include/config/prove/raw/lock/nesting.h) \
    $(wildcard include/config/preempt/lock.h) \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/lock/stat.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/rwlock_types.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/sched.h \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/virt/cpu/accounting/native.h) \
    $(wildcard include/config/sched/info.h) \
    $(wildcard include/config/schedstats.h) \
    $(wildcard include/config/fair/group/sched.h) \
    $(wildcard include/config/rt/group/sched.h) \
    $(wildcard include/config/rt/mutexes.h) \
    $(wildcard include/config/uclamp/task.h) \
    $(wildcard include/config/uclamp/buckets/count.h) \
    $(wildcard include/config/thread/info/in/task.h) \
    $(wildcard include/config/cgroup/sched.h) \
    $(wildcard include/config/preempt/notifiers.h) \
    $(wildcard include/config/blk/dev/io/trace.h) \
    $(wildcard include/config/preempt/rcu.h) \
    $(wildcard include/config/tasks/rcu.h) \
    $(wildcard include/config/tasks/trace/rcu.h) \
    $(wildcard include/config/psi.h) \
    $(wildcard include/config/memcg.h) \
    $(wildcard include/config/compat/brk.h) \
    $(wildcard include/config/cgroups.h) \
    $(wildcard include/config/blk/cgroup.h) \
    $(wildcard include/config/stackprotector.h) \
    $(wildcard include/config/arch/has/scaled/cputime.h) \
    $(wildcard include/config/virt/cpu/accounting/gen.h) \
    $(wildcard include/config/no/hz/full.h) \
    $(wildcard include/config/posix/cputimers.h) \
    $(wildcard include/config/posix/cpu/timers/task/work.h) \
    $(wildcard include/config/keys.h) \
    $(wildcard include/config/sysvipc.h) \
    $(wildcard include/config/detect/hung/task.h) \
    $(wildcard include/config/io/uring.h) \
    $(wildcard include/config/audit.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/debug/mutexes.h) \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/ubsan.h) \
    $(wildcard include/config/ubsan/trap.h) \
    $(wildcard include/config/block.h) \
    $(wildcard include/config/compaction.h) \
    $(wildcard include/config/task/xacct.h) \
    $(wildcard include/config/cpusets.h) \
    $(wildcard include/config/x86/cpu/resctrl.h) \
    $(wildcard include/config/futex.h) \
    $(wildcard include/config/compat.h) \
    $(wildcard include/config/perf/events.h) \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/numa/balancing.h) \
    $(wildcard include/config/rseq.h) \
    $(wildcard include/config/task/delay/acct.h) \
    $(wildcard include/config/fault/injection.h) \
    $(wildcard include/config/latencytop.h) \
    $(wildcard include/config/kunit.h) \
    $(wildcard include/config/function/graph/tracer.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/kcov.h) \
    $(wildcard include/config/uprobes.h) \
    $(wildcard include/config/bcache.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/vmap/stack.h) \
    $(wildcard include/config/livepatch.h) \
    $(wildcard include/config/security.h) \
    $(wildcard include/config/gcc/plugin/stackleak.h) \
    $(wildcard include/config/x86/mce.h) \
    $(wildcard include/config/arch/task/struct/on/stack.h) \
    $(wildcard include/config/preemption.h) \
    $(wildcard include/config/debug/rseq.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/sched.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/current.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/pid.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/rculist.h \
    $(wildcard include/config/prove/rcu/list.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
    $(wildcard include/config/page/poisoning/zero.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/preempt/rt.h) \
    $(wildcard include/config/panic/timeout.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/limits.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/limits.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/vdso/limits.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/linkage.h \
    $(wildcard include/config/arch/use/sym/annotations.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/stringify.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/export.h \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/module/rel/crcs.h) \
    $(wildcard include/config/have/arch/prel32/relocations.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/trim/unused/ksyms.h) \
    $(wildcard include/config/unused/symbols.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/linkage.h \
    $(wildcard include/config/arm64/bti/kernel.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/bitops.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/bitops.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/bitops/builtin-__ffs.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/bitops/builtin-ffs.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/bitops/builtin-__fls.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/bitops/builtin-fls.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/bitops/ffz.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/bitops/fls64.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/bitops/find.h \
    $(wildcard include/config/generic/find/first/bit.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/bitops/sched.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/bitops/hweight.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/bitops/arch_hweight.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/bitops/const_hweight.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/bitops/atomic.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/atomic.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/atomic.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/barrier.h \
    $(wildcard include/config/arm64/pseudo/nmi.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/barrier.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/cmpxchg.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/lse.h \
    $(wildcard include/config/arm64/lse/atomics.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/atomic_ll_sc.h \
    $(wildcard include/config/cc/has/k/constraint.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/atomic-arch-fallback.h \
    $(wildcard include/config/generic/atomic64.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/atomic-instrumented.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/instrumented.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/atomic-long.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/bitops/lock.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/bitops/non-atomic.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/bitops/le.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/bitops/ext2-atomic-setbit.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/minmax.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/typecheck.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/printk.h \
    $(wildcard include/config/message/loglevel/default.h) \
    $(wildcard include/config/console/loglevel/default.h) \
    $(wildcard include/config/console/loglevel/quiet.h) \
    $(wildcard include/config/early/printk.h) \
    $(wildcard include/config/printk/nmi.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/init.h \
    $(wildcard include/config/strict/kernel/rwx.h) \
    $(wildcard include/config/strict/module/rwx.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/kern_levels.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/kernel.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/sysinfo.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/cache.h \
    $(wildcard include/config/kasan/sw/tags.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/cputype.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/sysreg.h \
    $(wildcard include/config/broken/gas/inst.h) \
    $(wildcard include/config/arm64/pa/bits/52.h) \
    $(wildcard include/config/arm64/4k/pages.h) \
    $(wildcard include/config/arm64/16k/pages.h) \
    $(wildcard include/config/arm64/64k/pages.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/alternative.h \
    $(wildcard include/config/arm64/uao.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/cpucaps.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/insn.h \
  arch/arm64/include/generated/asm/div64.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/div64.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/rcupdate.h \
    $(wildcard include/config/tiny/rcu.h) \
    $(wildcard include/config/rcu/stall/common.h) \
    $(wildcard include/config/rcu/nocb/cpu.h) \
    $(wildcard include/config/tasks/rcu/generic.h) \
    $(wildcard include/config/tasks/rcu/trace.h) \
    $(wildcard include/config/tasks/rude/rcu.h) \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/debug/objects/rcu/head.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/prove/rcu.h) \
    $(wildcard include/config/rcu/boost.h) \
    $(wildcard include/config/arch/weak/release/acquire.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/irqflags.h \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/irqflags.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/ptrace.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/cpufeature.h \
    $(wildcard include/config/arm64/sw/ttbr0/pan.h) \
    $(wildcard include/config/arm64/sve.h) \
    $(wildcard include/config/arm64/cnp.h) \
    $(wildcard include/config/arm64/ptr/auth.h) \
    $(wildcard include/config/arm64/mte.h) \
    $(wildcard include/config/arm64/debug/priority/masking.h) \
    $(wildcard include/config/arm64/bti.h) \
    $(wildcard include/config/arm64/tlb/range.h) \
    $(wildcard include/config/arm64/pa/bits.h) \
    $(wildcard include/config/arm64/hw/afdbm.h) \
    $(wildcard include/config/arm64/amu/extn.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/hwcap.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/uapi/asm/hwcap.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/bug.h \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/bug/on/data/corruption.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/bug.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/asm-bug.h \
    $(wildcard include/config/debug/bugverbose.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/brk-imm.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/instrumentation.h \
    $(wildcard include/config/debug/entry.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/jump_label.h \
    $(wildcard include/config/jump/label.h) \
    $(wildcard include/config/have/arch/jump/label/relative.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/uapi/asm/ptrace.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/uapi/asm/sve_context.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/percpu.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/preempt.h \
    $(wildcard include/config/preempt/count.h) \
    $(wildcard include/config/trace/preempt/toggle.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/preempt.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/thread_info.h \
    $(wildcard include/config/have/arch/within/stack/frames.h) \
    $(wildcard include/config/hardened/usercopy.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/restart_block.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/time64.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/math64.h \
    $(wildcard include/config/arch/supports/int128.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/vdso/math64.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/vdso/time64.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/time.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/time_types.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/thread_info.h \
    $(wildcard include/config/shadow/call/stack.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/memory.h \
    $(wildcard include/config/arm64/va/bits.h) \
    $(wildcard include/config/kasan/shadow/offset.h) \
    $(wildcard include/config/debug/virtual.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
    $(wildcard include/config/efi.h) \
    $(wildcard include/config/arm/gic/v3/its.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/sizes.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/page-def.h \
    $(wildcard include/config/arm64/page/shift.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/mmdebug.h \
    $(wildcard include/config/debug/vm.h) \
    $(wildcard include/config/debug/vm/pgflags.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/memory_model.h \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/sparsemem.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/pfn.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/stack_pointer.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/percpu.h \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/threads.h \
    $(wildcard include/config/base/small.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/percpu-defs.h \
    $(wildcard include/config/debug/force/weak/per/cpu.h) \
    $(wildcard include/config/amd/mem/encrypt.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/bottom_half.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/lockdep.h \
    $(wildcard include/config/debug/locking/api/selftests.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/smp.h \
    $(wildcard include/config/up/late/init.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/errno.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/errno.h \
  arch/arm64/include/generated/uapi/asm/errno.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/asm-generic/errno.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/asm-generic/errno-base.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/cpumask.h \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/debug/per/cpu/maps.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/bitmap.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
    $(wildcard include/config/fortify/source.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/string.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/string.h \
    $(wildcard include/config/arch/has/uaccess/flushcache.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/smp_types.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/llist.h \
    $(wildcard include/config/arch/have/nmi/safe/cmpxchg.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/smp.h \
    $(wildcard include/config/arm64/acpi/parking/protocol.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/processor.h \
    $(wildcard include/config/kuser/helpers.h) \
    $(wildcard include/config/arm64/force/52bit.h) \
    $(wildcard include/config/have/hw/breakpoint.h) \
    $(wildcard include/config/arm64/tagged/addr/abi.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/vdso/processor.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/vdso/processor.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/hw_breakpoint.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/virt.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/sections.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/sections.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/kasan.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/pgtable-types.h \
    $(wildcard include/config/pgtable/levels.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/pgtable-nopud.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/pgtable-nop4d.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/pgtable-hwdef.h \
    $(wildcard include/config/arm64/cont/pte/shift.h) \
    $(wildcard include/config/arm64/cont/pmd/shift.h) \
    $(wildcard include/config/arm64/va/bits/52.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/pointer_auth.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/random.h \
    $(wildcard include/config/arch/random.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/once.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/random.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/ioctl.h \
  arch/arm64/include/generated/uapi/asm/ioctl.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/ioctl.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/asm-generic/ioctl.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/irqnr.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/irqnr.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/prandom.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/percpu.h \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/archrandom.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/spectre.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/fpsimd.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/uapi/asm/sigcontext.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/rcutree.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/wait.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/spinlock.h \
  arch/arm64/include/generated/asm/mmiowb.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/mmiowb.h \
    $(wildcard include/config/mmiowb.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/spinlock.h \
  arch/arm64/include/generated/asm/qrwlock.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/qrwlock.h \
  arch/arm64/include/generated/asm/qspinlock.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/qspinlock.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/rwlock.h \
    $(wildcard include/config/preempt.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/spinlock_api_smp.h \
    $(wildcard include/config/inline/spin/lock.h) \
    $(wildcard include/config/inline/spin/lock/bh.h) \
    $(wildcard include/config/inline/spin/lock/irq.h) \
    $(wildcard include/config/inline/spin/lock/irqsave.h) \
    $(wildcard include/config/inline/spin/trylock.h) \
    $(wildcard include/config/inline/spin/trylock/bh.h) \
    $(wildcard include/config/uninline/spin/unlock.h) \
    $(wildcard include/config/inline/spin/unlock/bh.h) \
    $(wildcard include/config/inline/spin/unlock/irq.h) \
    $(wildcard include/config/inline/spin/unlock/irqrestore.h) \
    $(wildcard include/config/generic/lockbreak.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/rwlock_api_smp.h \
    $(wildcard include/config/inline/read/lock.h) \
    $(wildcard include/config/inline/write/lock.h) \
    $(wildcard include/config/inline/read/lock/bh.h) \
    $(wildcard include/config/inline/write/lock/bh.h) \
    $(wildcard include/config/inline/read/lock/irq.h) \
    $(wildcard include/config/inline/write/lock/irq.h) \
    $(wildcard include/config/inline/read/lock/irqsave.h) \
    $(wildcard include/config/inline/write/lock/irqsave.h) \
    $(wildcard include/config/inline/read/trylock.h) \
    $(wildcard include/config/inline/write/trylock.h) \
    $(wildcard include/config/inline/read/unlock.h) \
    $(wildcard include/config/inline/write/unlock.h) \
    $(wildcard include/config/inline/read/unlock/bh.h) \
    $(wildcard include/config/inline/write/unlock/bh.h) \
    $(wildcard include/config/inline/read/unlock/irq.h) \
    $(wildcard include/config/inline/write/unlock/irq.h) \
    $(wildcard include/config/inline/read/unlock/irqrestore.h) \
    $(wildcard include/config/inline/write/unlock/irqrestore.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/wait.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/refcount.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/sem.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/sem.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/ipc.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/uidgid.h \
    $(wildcard include/config/multiuser.h) \
    $(wildcard include/config/user/ns.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/highuid.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/rhashtable-types.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/mutex.h \
    $(wildcard include/config/mutex/spin/on/owner.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/osq_lock.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/debug_locks.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/workqueue.h \
    $(wildcard include/config/debug/objects/work.h) \
    $(wildcard include/config/freezer.h) \
    $(wildcard include/config/sysfs.h) \
    $(wildcard include/config/wq/watchdog.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/timer.h \
    $(wildcard include/config/debug/objects/timers.h) \
    $(wildcard include/config/no/hz/common.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/ktime.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
    $(wildcard include/config/posix/timers.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/time32.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/timex.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/timex.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/timex.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/arch_timer.h \
    $(wildcard include/config/arm/arch/timer/ool/workaround.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/clocksource/arm_arch_timer.h \
    $(wildcard include/config/arm/arch/timer.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/timecounter.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/timex.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/vdso/time32.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/vdso/time.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/jiffies.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/vdso/jiffies.h \
  include/generated/timeconst.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/vdso/ktime.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/timekeeping.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/timekeeping32.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/debug/objects/free.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/ipc.h \
  arch/arm64/include/generated/uapi/asm/ipcbuf.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/asm-generic/ipcbuf.h \
  arch/arm64/include/generated/uapi/asm/sembuf.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/asm-generic/sembuf.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/shm.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/page.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/personality.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/personality.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/getorder.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/shm.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/asm-generic/hugetlb_encode.h \
  arch/arm64/include/generated/uapi/asm/shmbuf.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/asm-generic/shmbuf.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/shmparam.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/shmparam.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/kcov.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/kcov.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/plist.h \
    $(wildcard include/config/debug/plist.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/hrtimer.h \
    $(wildcard include/config/high/res/timers.h) \
    $(wildcard include/config/time/low/res.h) \
    $(wildcard include/config/timerfd.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/hrtimer_defs.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/rbtree.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/seqlock.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/ww_mutex.h \
    $(wildcard include/config/debug/ww/mutex/slowpath.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/timerqueue.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/seccomp.h \
    $(wildcard include/config/seccomp.h) \
    $(wildcard include/config/have/arch/seccomp/filter.h) \
    $(wildcard include/config/seccomp/filter.h) \
    $(wildcard include/config/checkpoint/restore.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/seccomp.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/seccomp.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/unistd.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/uapi/asm/unistd.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/asm-generic/unistd.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/seccomp.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/unistd.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/nodemask.h \
    $(wildcard include/config/highmem.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
    $(wildcard include/config/numa/keep/meminfo.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/resource.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/resource.h \
  arch/arm64/include/generated/uapi/asm/resource.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/resource.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/asm-generic/resource.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/latencytop.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/sched/prio.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/sched/types.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/signal_types.h \
    $(wildcard include/config/old/sigaction.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/signal.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/uapi/asm/signal.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/signal.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/asm-generic/signal.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/asm-generic/signal-defs.h \
  arch/arm64/include/generated/uapi/asm/siginfo.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/asm-generic/siginfo.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/mm_types_task.h \
    $(wildcard include/config/arch/want/batched/unmap/tlb/flush.h) \
    $(wildcard include/config/split/ptlock/cpus.h) \
    $(wildcard include/config/arch/enable/split/pmd/ptlock.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/task_io_accounting.h \
    $(wildcard include/config/task/io/accounting.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/posix-timers.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/alarmtimer.h \
    $(wildcard include/config/rtc/class.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/task_work.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/rseq.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/kcsan.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/energy_model.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/kobject.h \
    $(wildcard include/config/uevent/helper.h) \
    $(wildcard include/config/debug/kobject/release.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/sysfs.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/kernfs.h \
    $(wildcard include/config/kernfs.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/err.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/idr.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/radix-tree.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/xarray.h \
    $(wildcard include/config/xarray/multi.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/gfp.h \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/zone/dma32.h) \
    $(wildcard include/config/zone/device.h) \
    $(wildcard include/config/contig/alloc.h) \
    $(wildcard include/config/cma.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/memory/isolation.h) \
    $(wildcard include/config/zsmalloc.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/transparent/hugepage.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/page/extension.h) \
    $(wildcard include/config/deferred/struct/page/init.h) \
    $(wildcard include/config/have/memoryless/nodes.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/memory/hotremove.h) \
    $(wildcard include/config/have/arch/pfn/valid.h) \
    $(wildcard include/config/holes/in/zone.h) \
    $(wildcard include/config/arch/has/holes/memorymodel.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/page-flags-layout.h \
  include/generated/bounds.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/sparsemem.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/mm_types.h \
    $(wildcard include/config/have/aligned/struct/page.h) \
    $(wildcard include/config/userfaultfd.h) \
    $(wildcard include/config/swap.h) \
    $(wildcard include/config/have/arch/compat/mmap/bases.h) \
    $(wildcard include/config/membarrier.h) \
    $(wildcard include/config/aio.h) \
    $(wildcard include/config/mmu/notifier.h) \
    $(wildcard include/config/iommu/support.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/auxvec.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/auxvec.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/uapi/asm/auxvec.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/rwsem.h \
    $(wildcard include/config/rwsem/spin/on/owner.h) \
    $(wildcard include/config/debug/rwsems.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/completion.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/swait.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/uprobes.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/uprobes.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/debug-monitors.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/esr.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/probes.h \
    $(wildcard include/config/kprobes.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/mmu.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/page-flags.h \
    $(wildcard include/config/arch/uses/pg/uncached.h) \
    $(wildcard include/config/memory/failure.h) \
    $(wildcard include/config/idle/page/tracking.h) \
    $(wildcard include/config/thp/swap.h) \
    $(wildcard include/config/ksm.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/memory_hotplug.h \
    $(wildcard include/config/arch/has/add/pages.h) \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
    $(wildcard include/config/have/bootmem/info/node.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/notifier.h \
    $(wildcard include/config/tree/srcu.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/srcu.h \
    $(wildcard include/config/tiny/srcu.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/rcu_segcblist.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/srcutree.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/rcu_node_tree.h \
    $(wildcard include/config/rcu/fanout.h) \
    $(wildcard include/config/rcu/fanout/leaf.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/topology.h \
    $(wildcard include/config/use/percpu/numa/node/id.h) \
    $(wildcard include/config/sched/smt.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/arch_topology.h \
    $(wildcard include/config/generic/arch/topology.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/topology.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/topology.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/kconfig.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/local_lock.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/local_lock_internal.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/kobject_ns.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/stat.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/stat.h \
  arch/arm64/include/generated/uapi/asm/stat.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/asm-generic/stat.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/compat.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/compat.h \
    $(wildcard include/config/compat/for/u64/alignment.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/sched/task_stack.h \
    $(wildcard include/config/stack/growsup.h) \
    $(wildcard include/config/debug/stack/usage.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/magic.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/stat.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/kref.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/sched/cpufreq.h \
    $(wildcard include/config/cpu/freq.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/sched/topology.h \
    $(wildcard include/config/sched/debug.h) \
    $(wildcard include/config/sched/mc.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/sched/idle.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/sched/sd_flags.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/ioport.h \
    $(wildcard include/config/io/strict/devmem.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/klist.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/pm.h \
    $(wildcard include/config/vt/console/sleep.h) \
    $(wildcard include/config/pm.h) \
    $(wildcard include/config/pm/clk.h) \
    $(wildcard include/config/pm/generic/domains.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/overflow.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/device/bus.h \
    $(wildcard include/config/acpi.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/device/class.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/device/driver.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/device.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/pm_wakeup.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/uio.h \
    $(wildcard include/config/arch/has/copy/mc.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/uio.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/scatterlist.h \
    $(wildcard include/config/need/sg/dma/length.h) \
    $(wildcard include/config/debug/sg.h) \
    $(wildcard include/config/sgl/alloc.h) \
    $(wildcard include/config/arch/no/sg/chain.h) \
    $(wildcard include/config/sg/pool.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/mm.h \
    $(wildcard include/config/sysctl.h) \
    $(wildcard include/config/have/arch/mmap/rnd/bits.h) \
    $(wildcard include/config/have/arch/mmap/rnd/compat/bits.h) \
    $(wildcard include/config/mem/soft/dirty.h) \
    $(wildcard include/config/arch/uses/high/vma/flags.h) \
    $(wildcard include/config/arch/has/pkeys.h) \
    $(wildcard include/config/ppc.h) \
    $(wildcard include/config/x86.h) \
    $(wildcard include/config/parisc.h) \
    $(wildcard include/config/ia64.h) \
    $(wildcard include/config/sparc64.h) \
    $(wildcard include/config/arm64.h) \
    $(wildcard include/config/shmem.h) \
    $(wildcard include/config/dev/pagemap/ops.h) \
    $(wildcard include/config/device/private.h) \
    $(wildcard include/config/pci/p2pdma.h) \
    $(wildcard include/config/arch/has/pte/special.h) \
    $(wildcard include/config/arch/has/pte/devmap.h) \
    $(wildcard include/config/debug/vm/rb.h) \
    $(wildcard include/config/page/poisoning.h) \
    $(wildcard include/config/init/on/alloc/default/on.h) \
    $(wildcard include/config/init/on/free/default/on.h) \
    $(wildcard include/config/debug/pagealloc.h) \
    $(wildcard include/config/arch/has/set/direct/map.h) \
    $(wildcard include/config/hibernation.h) \
    $(wildcard include/config/hugetlbfs.h) \
    $(wildcard include/config/mapping/dirty/helpers.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/mmap_lock.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/range.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/percpu-refcount.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/bit_spinlock.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/shrinker.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/page_ext.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/stacktrace.h \
    $(wildcard include/config/stacktrace.h) \
    $(wildcard include/config/arch/stackwalk.h) \
    $(wildcard include/config/have/reliable/stacktrace.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/stackdepot.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/page_ref.h \
    $(wildcard include/config/debug/page/ref.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/tracepoint-defs.h \
    $(wildcard include/config/tracepoints.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/static_key.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/memremap.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/pgtable.h \
    $(wildcard include/config/highpte.h) \
    $(wildcard include/config/have/arch/transparent/hugepage/pud.h) \
    $(wildcard include/config/have/arch/soft/dirty.h) \
    $(wildcard include/config/arch/enable/thp/migration.h) \
    $(wildcard include/config/have/arch/huge/vmap.h) \
    $(wildcard include/config/x86/espfix64.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/pgtable.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/proc-fns.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/mte.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/pgtable-prot.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/tlbflush.h \
    $(wildcard include/config/arm64/workaround/repeat/tlbi.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/bitfield.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/fixmap.h \
    $(wildcard include/config/acpi/apei/ghes.h) \
    $(wildcard include/config/arm/sde/interface.h) \
    $(wildcard include/config/unmap/kernel/at/el0.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/boot.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/fixmap.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/pgtable_uffd.h \
    $(wildcard include/config/have/arch/userfaultfd/wp.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/huge_mm.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/sched/coredump.h \
    $(wildcard include/config/core/dump/default/elf/headers.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/fs.h \
    $(wildcard include/config/read/only/thp/for/fs.h) \
    $(wildcard include/config/fs/posix/acl.h) \
    $(wildcard include/config/cgroup/writeback.h) \
    $(wildcard include/config/ima.h) \
    $(wildcard include/config/file/locking.h) \
    $(wildcard include/config/fsnotify.h) \
    $(wildcard include/config/fs/encryption.h) \
    $(wildcard include/config/fs/verity.h) \
    $(wildcard include/config/epoll.h) \
    $(wildcard include/config/unicode.h) \
    $(wildcard include/config/quota.h) \
    $(wildcard include/config/fs/dax.h) \
    $(wildcard include/config/mandatory/file/locking.h) \
    $(wildcard include/config/migration.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/wait_bit.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/kdev_t.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/kdev_t.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/dcache.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/rculist_bl.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/list_bl.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/lockref.h \
    $(wildcard include/config/arch/use/cmpxchg/lockref.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/stringhash.h \
    $(wildcard include/config/dcache/word/access.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/hash.h \
    $(wildcard include/config/have/arch/hash.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/path.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/list_lru.h \
    $(wildcard include/config/memcg/kmem.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/capability.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/capability.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/semaphore.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/fcntl.h \
    $(wildcard include/config/arch/32bit/off/t.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/fcntl.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/uapi/asm/fcntl.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/asm-generic/fcntl.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/openat2.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/migrate_mode.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/percpu-rwsem.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/rcuwait.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/sched/signal.h \
    $(wildcard include/config/sched/autogroup.h) \
    $(wildcard include/config/bsd/process/acct.h) \
    $(wildcard include/config/taskstats.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/signal.h \
    $(wildcard include/config/proc/fs.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/sched/jobctl.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/sched/task.h \
    $(wildcard include/config/have/exit/thread.h) \
    $(wildcard include/config/arch/wants/dynamic/task/struct.h) \
    $(wildcard include/config/have/arch/thread/struct/whitelist.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/uaccess.h \
    $(wildcard include/config/set/fs.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/fault-inject-usercopy.h \
    $(wildcard include/config/fault/injection/usercopy.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/uaccess.h \
    $(wildcard include/config/arm64/pan.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/kernel-pgtable.h \
    $(wildcard include/config/randomize/base.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/extable.h \
    $(wildcard include/config/bpf/jit.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/cred.h \
    $(wildcard include/config/debug/credentials.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/key.h \
    $(wildcard include/config/key/notifications.h) \
    $(wildcard include/config/net.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/sysctl.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/sysctl.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/assoc_array.h \
    $(wildcard include/config/associative/array.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/sched/user.h \
    $(wildcard include/config/fanotify.h) \
    $(wildcard include/config/posix/mqueue.h) \
    $(wildcard include/config/bpf/syscall.h) \
    $(wildcard include/config/watch/queue.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/rcu_sync.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/delayed_call.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/uuid.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/uuid.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/errseq.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/ioprio.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/sched/rt.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/iocontext.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/fs_types.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/fs.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/quota.h \
    $(wildcard include/config/quota/netlink/interface.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/percpu_counter.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/dqblk_xfs.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/dqblk_v1.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/dqblk_v2.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/dqblk_qtree.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/projid.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/quota.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/nfs_fs_i.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/vmstat.h \
    $(wildcard include/config/vm/event/counters.h) \
    $(wildcard include/config/debug/tlbflush.h) \
    $(wildcard include/config/debug/vm/vmacache.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/vm_event_item.h \
    $(wildcard include/config/memory/balloon.h) \
    $(wildcard include/config/balloon/compaction.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/io.h \
  arch/arm64/include/generated/asm/early_ioremap.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/early_ioremap.h \
    $(wildcard include/config/generic/early/ioremap.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/io.h \
    $(wildcard include/config/generic/iomap.h) \
    $(wildcard include/config/generic/ioremap.h) \
    $(wildcard include/config/has/ioport/map.h) \
    $(wildcard include/config/virt/to/bus.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/pci_iomap.h \
    $(wildcard include/config/pci.h) \
    $(wildcard include/config/no/generic/pci/ioport/map.h) \
    $(wildcard include/config/generic/pci/iomap.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/logic_pio.h \
    $(wildcard include/config/indirect/pio.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/fwnode.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/vmalloc.h \
    $(wildcard include/config/kasan/vmalloc.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/vmalloc.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/dma-mapping.h \
    $(wildcard include/config/dma/api/debug.h) \
    $(wildcard include/config/has/dma.h) \
    $(wildcard include/config/need/dma/map/state.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/dma-direction.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/mem_encrypt.h \
    $(wildcard include/config/arch/has/mem/encrypt.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/module.h \
    $(wildcard include/config/modules/tree/lookup.h) \
    $(wildcard include/config/module/sig.h) \
    $(wildcard include/config/kallsyms.h) \
    $(wildcard include/config/bpf/events.h) \
    $(wildcard include/config/event/tracing.h) \
    $(wildcard include/config/have/static/call/inline.h) \
    $(wildcard include/config/module/unload.h) \
    $(wildcard include/config/constructors.h) \
    $(wildcard include/config/function/error/injection.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/kmod.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/umh.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/elf.h \
    $(wildcard include/config/arch/use/gnu/property.h) \
    $(wildcard include/config/arch/have/elf/prot.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/elf.h \
    $(wildcard include/config/compat/vdso.h) \
  arch/arm64/include/generated/asm/user.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/user.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/elf.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/elf-em.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/moduleparam.h \
    $(wildcard include/config/alpha.h) \
    $(wildcard include/config/ppc64.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/rbtree_latch.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/error-injection.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/error-injection.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/static_call_types.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/module.h \
    $(wildcard include/config/arm64/module/plts.h) \
    $(wildcard include/config/dynamic/ftrace.h) \
    $(wildcard include/config/arm64/erratum/843419.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/module.h \
    $(wildcard include/config/have/mod/arch/specific.h) \
    $(wildcard include/config/modules/use/elf/rel.h) \
    $(wildcard include/config/modules/use/elf/rela.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/slab.h \
    $(wildcard include/config/debug/slab.h) \
    $(wildcard include/config/failslab.h) \
    $(wildcard include/config/have/hardened/usercopy/allocator.h) \
    $(wildcard include/config/slab.h) \
    $(wildcard include/config/slub.h) \
    $(wildcard include/config/slob.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/kasan.h \
    $(wildcard include/config/kasan/generic.h) \
    $(wildcard include/config/kasan/inline.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/cdev.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/netdevice.h \
    $(wildcard include/config/dcb.h) \
    $(wildcard include/config/hyperv/net.h) \
    $(wildcard include/config/wlan.h) \
    $(wildcard include/config/ax25.h) \
    $(wildcard include/config/mac80211/mesh.h) \
    $(wildcard include/config/net/ipip.h) \
    $(wildcard include/config/net/ipgre.h) \
    $(wildcard include/config/ipv6/sit.h) \
    $(wildcard include/config/ipv6/tunnel.h) \
    $(wildcard include/config/rps.h) \
    $(wildcard include/config/netpoll.h) \
    $(wildcard include/config/xps.h) \
    $(wildcard include/config/xdp/sockets.h) \
    $(wildcard include/config/bql.h) \
    $(wildcard include/config/rfs/accel.h) \
    $(wildcard include/config/fcoe.h) \
    $(wildcard include/config/xfrm/offload.h) \
    $(wildcard include/config/net/poll/controller.h) \
    $(wildcard include/config/libfcoe.h) \
    $(wildcard include/config/wireless/ext.h) \
    $(wildcard include/config/net/l3/master/dev.h) \
    $(wildcard include/config/ipv6.h) \
    $(wildcard include/config/tls/device.h) \
    $(wildcard include/config/vlan/8021q.h) \
    $(wildcard include/config/net/dsa.h) \
    $(wildcard include/config/tipc.h) \
    $(wildcard include/config/irda.h) \
    $(wildcard include/config/atalk.h) \
    $(wildcard include/config/decnet.h) \
    $(wildcard include/config/mpls/routing.h) \
    $(wildcard include/config/net/cls/act.h) \
    $(wildcard include/config/netfilter/ingress.h) \
    $(wildcard include/config/net/sched.h) \
    $(wildcard include/config/garp.h) \
    $(wildcard include/config/mrp.h) \
    $(wildcard include/config/cgroup/net/prio.h) \
    $(wildcard include/config/macsec.h) \
    $(wildcard include/config/net/flow/limit.h) \
    $(wildcard include/config/ethtool/netlink.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/delay.h \
  arch/arm64/include/generated/asm/delay.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/delay.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/prefetch.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/dynamic_queue_limits.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/ethtool.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/compat.h \
    $(wildcard include/config/arch/has/syscall/wrapper.h) \
    $(wildcard include/config/x86/x32/abi.h) \
    $(wildcard include/config/compat/old/sigaction.h) \
    $(wildcard include/config/odd/rt/sigaction.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/socket.h \
  arch/arm64/include/generated/uapi/asm/socket.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/asm-generic/socket.h \
  arch/arm64/include/generated/uapi/asm/sockios.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/asm-generic/sockios.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/sockios.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/socket.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/if.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/libc-compat.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/hdlc/ioctl.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/aio_abi.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/syscall_wrapper.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/ethtool.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/if_ether.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/skbuff.h \
    $(wildcard include/config/nf/conntrack.h) \
    $(wildcard include/config/bridge/netfilter.h) \
    $(wildcard include/config/net/tc/skb/ext.h) \
    $(wildcard include/config/skb/extensions.h) \
    $(wildcard include/config/ipv6/ndisc/nodetype.h) \
    $(wildcard include/config/net/switchdev.h) \
    $(wildcard include/config/net/redirect.h) \
    $(wildcard include/config/net/rx/busy/poll.h) \
    $(wildcard include/config/network/secmark.h) \
    $(wildcard include/config/have/efficient/unaligned/access.h) \
    $(wildcard include/config/network/phy/timestamping.h) \
    $(wildcard include/config/xfrm.h) \
    $(wildcard include/config/mptcp.h) \
    $(wildcard include/config/netfilter/xt/target/trace.h) \
    $(wildcard include/config/nf/tables.h) \
    $(wildcard include/config/ip/vs.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/bvec.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/net.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/sockptr.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/net.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/textsearch.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/checksum.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/checksum.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/in6.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/in6.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/checksum.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/netdev_features.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/sched/clock.h \
    $(wildcard include/config/have/unstable/sched/clock.h) \
    $(wildcard include/config/irq/time/accounting.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/flow_dissector.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/siphash.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/if_ether.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/splice.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/pipe_fs_i.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/if_packet.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/flow.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/netfilter/nf_conntrack_common.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/netfilter/nf_conntrack_common.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/net_namespace.h \
    $(wildcard include/config/ieee802154/6lowpan.h) \
    $(wildcard include/config/ip/sctp.h) \
    $(wildcard include/config/ip/dccp.h) \
    $(wildcard include/config/netfilter.h) \
    $(wildcard include/config/nf/defrag/ipv6.h) \
    $(wildcard include/config/netfilter/netlink/acct.h) \
    $(wildcard include/config/nf/ct/netlink/timeout.h) \
    $(wildcard include/config/wext/core.h) \
    $(wildcard include/config/mpls.h) \
    $(wildcard include/config/can.h) \
    $(wildcard include/config/crypto/user.h) \
    $(wildcard include/config/net/ns.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/netns/core.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/netns/mib.h \
    $(wildcard include/config/xfrm/statistics.h) \
    $(wildcard include/config/tls.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/snmp.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/snmp.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/u64_stats_sync.h \
  arch/arm64/include/generated/asm/local64.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/local64.h \
  arch/arm64/include/generated/asm/local.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/local.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/netns/unix.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/netns/packet.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/netns/ipv4.h \
    $(wildcard include/config/ip/multiple/tables.h) \
    $(wildcard include/config/ip/route/classid.h) \
    $(wildcard include/config/ip/mroute.h) \
    $(wildcard include/config/ip/mroute/multiple/tables.h) \
    $(wildcard include/config/ip/route/multipath.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/inet_frag.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/netns/ipv6.h \
    $(wildcard include/config/ipv6/multiple/tables.h) \
    $(wildcard include/config/ipv6/subtrees.h) \
    $(wildcard include/config/ipv6/mroute.h) \
    $(wildcard include/config/ipv6/mroute/multiple/tables.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/dst_ops.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/icmpv6.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/netns/nexthop.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/netns/ieee802154_6lowpan.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/netns/sctp.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/netns/dccp.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/netns/netfilter.h \
    $(wildcard include/config/netfilter/family/arp.h) \
    $(wildcard include/config/netfilter/family/bridge.h) \
    $(wildcard include/config/nf/defrag/ipv4.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/netfilter_defs.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/netfilter.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/in.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/in.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/netns/x_tables.h \
    $(wildcard include/config/bridge/nf/ebtables.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/netns/conntrack.h \
    $(wildcard include/config/nf/ct/proto/dccp.h) \
    $(wildcard include/config/nf/ct/proto/sctp.h) \
    $(wildcard include/config/nf/ct/proto/gre.h) \
    $(wildcard include/config/nf/conntrack/events.h) \
    $(wildcard include/config/nf/conntrack/labels.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/list_nulls.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/netfilter/nf_conntrack_tcp.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/netfilter/nf_conntrack_tcp.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/netfilter/nf_conntrack_dccp.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/netfilter/nf_conntrack_tuple_common.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/netfilter/nf_conntrack_sctp.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/netfilter/nf_conntrack_sctp.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/netns/nftables.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/netns/xfrm.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/xfrm.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/netns/mpls.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/netns/can.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/netns/xdp.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/netns/bpf.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/bpf-netns.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/bpf.h \
    $(wildcard include/config/efficient/unaligned/access.h) \
    $(wildcard include/config/cgroup/net/classid.h) \
    $(wildcard include/config/bpf/kprobe/override.h) \
    $(wildcard include/config/bpf/lirc/mode2.h) \
    $(wildcard include/config/sock/cgroup/data.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/bpf_common.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/ns_common.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/seq_file_net.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/seq_file.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/nsproxy.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/netprio_cgroup.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/cgroup.h \
    $(wildcard include/config/cgroup/cpuacct.h) \
    $(wildcard include/config/cgroup/data.h) \
    $(wildcard include/config/cgroup/bpf.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/cgroupstats.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/taskstats.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/user_namespace.h \
    $(wildcard include/config/inotify/user.h) \
    $(wildcard include/config/persistent/keyrings.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/kernel_stat.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/interrupt.h \
    $(wildcard include/config/irq/forced/threading.h) \
    $(wildcard include/config/generic/irq/probe.h) \
    $(wildcard include/config/irq/timings.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/irqreturn.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/hardirq.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/context_tracking_state.h \
    $(wildcard include/config/context/tracking.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/ftrace_irq.h \
    $(wildcard include/config/hwlat/tracer.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/vtime.h \
    $(wildcard include/config/virt/cpu/accounting.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/hardirq.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/irq.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/asm-generic/irq.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/asm/kvm_arm.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/irq_cpustat.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/cgroup-defs.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/bpf-cgroup.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/bpf.h \
    $(wildcard include/config/bpf/stream/parser.h) \
    $(wildcard include/config/inet.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/file.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/kallsyms.h \
    $(wildcard include/config/kallsyms/all.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/psi_types.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/kthread.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/cgroup_subsys.h \
    $(wildcard include/config/cgroup/device.h) \
    $(wildcard include/config/cgroup/freezer.h) \
    $(wildcard include/config/cgroup/perf.h) \
    $(wildcard include/config/cgroup/hugetlb.h) \
    $(wildcard include/config/cgroup/pids.h) \
    $(wildcard include/config/cgroup/rdma.h) \
    $(wildcard include/config/cgroup/debug.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/xdp.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/neighbour.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/netlink.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/net/scm.h \
    $(wildcard include/config/security/network.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/security.h \
    $(wildcard include/config/security/infiniband.h) \
    $(wildcard include/config/security/network/xfrm.h) \
    $(wildcard include/config/security/path.h) \
    $(wildcard include/config/securityfs.h) \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/kernel_read_file.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/netlink.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/netdevice.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/if_link.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/if_link.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/if_bonding.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/pkt_cls.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi/linux/pkt_sched.h \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/hashtable.h \

/mnt/samba/petalinux/zcu102/work/dma/dma_copy_test.o: $(deps_/mnt/samba/petalinux/zcu102/work/dma/dma_copy_test.o)

$(deps_/mnt/samba/petalinux/zcu102/work/dma/dma_copy_test.o):
