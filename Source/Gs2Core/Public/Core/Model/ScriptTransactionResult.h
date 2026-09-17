/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 */

#pragma once

#include "CoreMinimal.h"
#include "Core/Gs2Object.h"
#include "TransactionResult.h"

namespace Gs2::Core::Model
{
    class GS2CORE_API FScriptTransactionResult final : public FGs2Object, public TSharedFromThis<FScriptTransactionResult>
    {
        TOptional<FString> ScriptIdValue;
        TOptional<FString> TransactionIdValue;
        TSharedPtr<FTransactionResult> TransactionResultValue;

    public:
        FScriptTransactionResult();
        FScriptTransactionResult(
            const FScriptTransactionResult& From
        );
        virtual ~FScriptTransactionResult() override = default;

        TSharedPtr<FScriptTransactionResult> WithScriptId(const TOptional<FString> ScriptId);
        TSharedPtr<FScriptTransactionResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FScriptTransactionResult> WithTransactionResult(const TSharedPtr<FTransactionResult> TransactionResult);

        TOptional<FString> GetScriptId() const;
        TOptional<FString> GetTransactionId() const;
        TSharedPtr<FTransactionResult> GetTransactionResult() const;

        static TSharedPtr<FScriptTransactionResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FScriptTransactionResult, ESPMode::ThreadSafe> FScriptTransactionResultPtr;
}
