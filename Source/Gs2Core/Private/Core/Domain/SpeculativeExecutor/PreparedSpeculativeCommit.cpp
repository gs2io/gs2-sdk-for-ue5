/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 */

#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"

namespace Gs2::Core::Domain::SpeculativeExecutor
{
    FPreparedSpeculativeCommit::FPreparedSpeculativeCommit(
        const TSharedPtr<TFunction<void()>>& LegacyCommit,
        const FString& CompositionKey,
        FComposeFunction Compose,
        FStateCommitFunction StateCommit,
        FGuardFunction Guard
    ):
        LegacyCommit(LegacyCommit),
        CompositionKey(CompositionKey),
        Compose(MoveTemp(Compose)),
        StateCommit(MoveTemp(StateCommit)),
        Guard(MoveTemp(Guard))
    {
    }

    TSharedPtr<FPreparedSpeculativeCommit> FPreparedSpeculativeCommit::WrapLegacy(
        const TSharedPtr<TFunction<void()>>& Commit
    )
    {
        if (!Commit.IsValid()) return nullptr;
        return MakeShareable(new FPreparedSpeculativeCommit(
            Commit,
            FString(),
            FComposeFunction(),
            FStateCommitFunction(),
            FGuardFunction()
        ));
    }

    TSharedPtr<FPreparedSpeculativeCommit> FPreparedSpeculativeCommit::CreateComposable(
        const FString& CompositionKey,
        FComposeFunction Compose,
        FStateCommitFunction Commit,
        FGuardFunction Guard
    )
    {
        if (!Compose || !Commit) return nullptr;
        return MakeShareable(new FPreparedSpeculativeCommit(
            nullptr,
            CompositionKey,
            MoveTemp(Compose),
            MoveTemp(Commit),
            MoveTemp(Guard)
        ));
    }

    TSharedPtr<FPreparedSpeculativeCommit> FPreparedSpeculativeCommit::CreateGuarded(
        const TSharedPtr<TFunction<void()>>& Commit,
        FGuardFunction Guard
    )
    {
        if (!Commit.IsValid() || !Guard) return nullptr;
        return MakeShareable(new FPreparedSpeculativeCommit(
            Commit,
            FString(),
            FComposeFunction(),
            FStateCommitFunction(),
            MoveTemp(Guard)
        ));
    }

    bool FPreparedSpeculativeCommit::IsComposable() const
    {
        return static_cast<bool>(Compose) && static_cast<bool>(StateCommit);
    }

    bool FPreparedSpeculativeCommit::IsGuarded() const
    {
        return static_cast<bool>(Guard);
    }

    bool FPreparedSpeculativeCommit::IsStillSatisfied() const
    {
        return !Guard || Guard();
    }

    const FString& FPreparedSpeculativeCommit::GetCompositionKey() const
    {
        return CompositionKey;
    }

    bool FPreparedSpeculativeCommit::TryCompose(
        const TSharedPtr<void>& Current,
        const bool HasCurrent,
        TSharedPtr<void>& Next
    ) const
    {
        return IsComposable() && Compose(Current, HasCurrent, Next);
    }

    void FPreparedSpeculativeCommit::Commit(const TSharedPtr<void>& State) const
    {
        if (IsComposable())
        {
            StateCommit(State);
        }
    }

    void FPreparedSpeculativeCommit::InvokeLegacy() const
    {
        if (LegacyCommit.IsValid() && IsStillSatisfied())
        {
            (*LegacyCommit)();
        }
    }

    TSharedPtr<TFunction<void()>> FPreparedSpeculativeCommit::BuildAtomicCommit(
        const TSharedPtr<FPreparedCommitArray>& Commits,
        const int32 ExpectedActionCount
    )
    {
        if (!Commits.IsValid() || ExpectedActionCount < 0 || Commits->Num() > ExpectedActionCount)
        {
            return nullptr;
        }
        const auto Snapshot = *Commits;
        TArray<FPreparedCommitPtr> Prepared;
        for (const auto& Commit : Snapshot)
        {
            if (Commit.IsValid()) Prepared.Add(Commit);
        }
        if (Prepared.Num() == 0 && ExpectedActionCount != 0)
        {
            return nullptr;
        }
        return MakeShared<TFunction<void()>>([Prepared]()
        {
            FPreparedCommitPtr PendingTarget;
            TSharedPtr<void> PendingValue;
            bool PendingValid = false;
            const auto Flush = [&]()
            {
                if (PendingValid && PendingTarget.IsValid()) PendingTarget->Commit(PendingValue);
                PendingTarget = nullptr;
                PendingValue = nullptr;
                PendingValid = false;
            };
            for (const auto& Commit : Prepared)
            {
                if (!Commit->IsComposable())
                {
                    Flush();
                    Commit->InvokeLegacy();
                    continue;
                }
                if (!PendingTarget.IsValid() || PendingTarget->GetCompositionKey() != Commit->GetCompositionKey())
                {
                    Flush();
                    PendingTarget = Commit;
                    PendingValid = PendingTarget->TryCompose(nullptr, false, PendingValue);
                    continue;
                }
                if (!PendingValid) continue;
                TSharedPtr<void> Next;
                PendingValid = Commit->TryCompose(PendingValue, true, Next);
                PendingTarget = Commit;
                PendingValue = Next;
            }
            Flush();
        });
    }

    TSharedPtr<TFunction<void()>> FPreparedSpeculativeCommit::BuildAtomicCommit(
        const TSharedPtr<TArray<TSharedPtr<TFunction<void()>>>>& Commits,
        const int32 ExpectedActionCount
    )
    {
        if (!Commits.IsValid()) return nullptr;
        const auto Prepared = MakeShared<FPreparedCommitArray>();
        for (const auto& Commit : *Commits)
        {
            Prepared->Add(FPreparedSpeculativeCommit::WrapLegacy(Commit));
        }
        return BuildAtomicCommit(Prepared, ExpectedActionCount);
    }

    TSharedPtr<TFunction<void()>> FPreparedSpeculativeCommit::BuildAtomicVerificationCommit(
        const TSharedPtr<FPreparedCommitArray>& Commits,
        const int32 ExpectedActionCount
    )
    {
        const auto Prepared = BuildAtomicVerificationPreparedCommit(Commits, ExpectedActionCount);
        if (!Prepared.IsValid()) return nullptr;
        return MakeShared<TFunction<void()>>([Prepared]()
        {
            Prepared->InvokeLegacy();
        });
    }

    FPreparedSpeculativeCommit::FPreparedCommitPtr FPreparedSpeculativeCommit::BuildAtomicVerificationPreparedCommit(
        const TSharedPtr<FPreparedCommitArray>& Commits,
        const int32 ExpectedActionCount
    )
    {
        if (!Commits.IsValid()) return nullptr;
        const auto Snapshot = *Commits;
        for (const auto& Commit : Snapshot)
        {
            if (!Commit.IsValid() || !Commit->IsGuarded()) return nullptr;
        }
        const auto SnapshotCommits = MakeShared<FPreparedCommitArray>();
        *SnapshotCommits = Snapshot;
        const auto AtomicCommit = BuildAtomicCommit(SnapshotCommits, ExpectedActionCount);
        if (!AtomicCommit.IsValid()) return nullptr;
        return FPreparedSpeculativeCommit::CreateGuarded(
            AtomicCommit,
            [Snapshot]()
            {
                for (const auto& Commit : Snapshot)
                {
                    if (!Commit->IsStillSatisfied()) return false;
                }
                return true;
            }
        );
    }


}
