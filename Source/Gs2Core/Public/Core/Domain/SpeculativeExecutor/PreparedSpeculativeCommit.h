/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 */

#pragma once

#include "CoreMinimal.h"

namespace Gs2::Core::Domain::SpeculativeExecutor
{
    class GS2CORE_API FPreparedSpeculativeCommit
    {
    public:
        using FPreparedCommitPtr = TSharedPtr<FPreparedSpeculativeCommit>;
        using FPreparedCommitArray = TArray<FPreparedCommitPtr>;
        using FComposeFunction = TFunction<bool(
            const TSharedPtr<void>& Current,
            bool HasCurrent,
            TSharedPtr<void>& Next
        )>;
        using FStateCommitFunction = TFunction<void(const TSharedPtr<void>& State)>;
        using FGuardFunction = TFunction<bool()>;

        static FPreparedCommitPtr WrapLegacy(
            const TSharedPtr<TFunction<void()>>& Commit
        );
        static FPreparedCommitPtr CreateComposable(
            const FString& CompositionKey,
            FComposeFunction Compose,
            FStateCommitFunction Commit,
            FGuardFunction Guard = FGuardFunction()
        );
        static FPreparedCommitPtr CreateGuarded(
            const TSharedPtr<TFunction<void()>>& Commit,
            FGuardFunction Guard
        );
        static TSharedPtr<TFunction<void()>> BuildAtomicCommit(
            const TSharedPtr<FPreparedCommitArray>& Commits,
            int32 ExpectedActionCount
        );
        static TSharedPtr<TFunction<void()>> BuildAtomicCommit(
            const TSharedPtr<TArray<TSharedPtr<TFunction<void()>>>>& Commits,
            int32 ExpectedActionCount
        );
        static TSharedPtr<TFunction<void()>> BuildAtomicVerificationCommit(
            const TSharedPtr<FPreparedCommitArray>& Commits,
            int32 ExpectedActionCount
        );
        static FPreparedCommitPtr BuildAtomicVerificationPreparedCommit(
            const TSharedPtr<FPreparedCommitArray>& Commits,
            int32 ExpectedActionCount
        );

        bool IsComposable() const;
        bool IsGuarded() const;
        bool IsStillSatisfied() const;
        const FString& GetCompositionKey() const;
        bool TryCompose(
            const TSharedPtr<void>& Current,
            bool HasCurrent,
            TSharedPtr<void>& Next
        ) const;
        void Commit(const TSharedPtr<void>& State) const;
        void InvokeLegacy() const;

    private:
        FPreparedSpeculativeCommit(
            const TSharedPtr<TFunction<void()>>& LegacyCommit,
            const FString& CompositionKey,
            FComposeFunction Compose,
            FStateCommitFunction StateCommit,
            FGuardFunction Guard
        );

        const TSharedPtr<TFunction<void()>> LegacyCommit;
        const FString CompositionKey;
        const FComposeFunction Compose;
        const FStateCommitFunction StateCommit;
        const FGuardFunction Guard;
    };
}
