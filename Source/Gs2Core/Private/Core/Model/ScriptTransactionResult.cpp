/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 */

#include "Core/Model/ScriptTransactionResult.h"

namespace Gs2::Core::Model
{
    FScriptTransactionResult::FScriptTransactionResult():
        ScriptIdValue(TOptional<FString>()),
        TransactionIdValue(TOptional<FString>()),
        TransactionResultValue(nullptr)
    {
    }

    FScriptTransactionResult::FScriptTransactionResult(
        const FScriptTransactionResult& From
    ):
        ScriptIdValue(From.ScriptIdValue),
        TransactionIdValue(From.TransactionIdValue),
        TransactionResultValue(From.TransactionResultValue)
    {
    }

    TSharedPtr<FScriptTransactionResult> FScriptTransactionResult::WithScriptId(
        const TOptional<FString> ScriptId
    )
    {
        this->ScriptIdValue = ScriptId;
        return SharedThis(this);
    }

    TSharedPtr<FScriptTransactionResult> FScriptTransactionResult::WithTransactionId(
        const TOptional<FString> TransactionId
    )
    {
        this->TransactionIdValue = TransactionId;
        return SharedThis(this);
    }

    TSharedPtr<FScriptTransactionResult> FScriptTransactionResult::WithTransactionResult(
        const TSharedPtr<FTransactionResult> TransactionResult
    )
    {
        this->TransactionResultValue = TransactionResult;
        return SharedThis(this);
    }

    TOptional<FString> FScriptTransactionResult::GetScriptId() const
    {
        return ScriptIdValue;
    }

    TOptional<FString> FScriptTransactionResult::GetTransactionId() const
    {
        return TransactionIdValue;
    }

    TSharedPtr<FTransactionResult> FScriptTransactionResult::GetTransactionResult() const
    {
        return TransactionResultValue;
    }

    TSharedPtr<FScriptTransactionResult> FScriptTransactionResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FScriptTransactionResult>()
            ->WithScriptId(Data->HasField(ANSI_TO_TCHAR("scriptId")) ? [Data]() -> TOptional<FString>
                {
                    FString Value;
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("scriptId"), Value))
                    {
                        return TOptional<FString>(Value);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTransactionId(Data->HasField(ANSI_TO_TCHAR("transactionId")) ? [Data]() -> TOptional<FString>
                {
                    FString Value;
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("transactionId"), Value))
                    {
                        return TOptional<FString>(Value);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTransactionResult(
                Data->HasField(ANSI_TO_TCHAR("transactionResult")) &&
                !Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("transactionResult")) &&
                Data->HasTypedField<EJson::Object>(ANSI_TO_TCHAR("transactionResult"))
                    ? FTransactionResult::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("transactionResult")))
                    : nullptr
            );
    }

    TSharedPtr<FJsonObject> FScriptTransactionResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ScriptIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("scriptId"), ScriptIdValue.GetValue());
        }
        if (TransactionIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("transactionId"), TransactionIdValue.GetValue());
        }
        if (TransactionResultValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("transactionResult"), TransactionResultValue->ToJson());
        }
        return JsonRootObject;
    }

    FString FScriptTransactionResult::TypeName = "ScriptTransactionResult";
}
