/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include "Distributor/Model/TransactionResult.h"

namespace Gs2::Distributor::Model
{
    FTransactionResult::FTransactionResult():
        TransactionResultIdValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        TransactionIdValue(TOptional<FString>()),
        VerifyResultsValue(nullptr),
        ConsumeResultsValue(nullptr),
        AcquireResultsValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FTransactionResult::FTransactionResult(
        const FTransactionResult& From
    ):
        TransactionResultIdValue(From.TransactionResultIdValue),
        UserIdValue(From.UserIdValue),
        TransactionIdValue(From.TransactionIdValue),
        VerifyResultsValue(From.VerifyResultsValue),
        ConsumeResultsValue(From.ConsumeResultsValue),
        AcquireResultsValue(From.AcquireResultsValue),
        CreatedAtValue(From.CreatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FTransactionResult> FTransactionResult::WithTransactionResultId(
        const TOptional<FString> TransactionResultId
    )
    {
        this->TransactionResultIdValue = TransactionResultId;
        return SharedThis(this);
    }

    TSharedPtr<FTransactionResult> FTransactionResult::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FTransactionResult> FTransactionResult::WithTransactionId(
        const TOptional<FString> TransactionId
    )
    {
        this->TransactionIdValue = TransactionId;
        return SharedThis(this);
    }

    TSharedPtr<FTransactionResult> FTransactionResult::WithVerifyResults(
        const TSharedPtr<TArray<TSharedPtr<Model::FVerifyActionResult>>> VerifyResults
    )
    {
        this->VerifyResultsValue = VerifyResults;
        return SharedThis(this);
    }

    TSharedPtr<FTransactionResult> FTransactionResult::WithConsumeResults(
        const TSharedPtr<TArray<TSharedPtr<Model::FConsumeActionResult>>> ConsumeResults
    )
    {
        this->ConsumeResultsValue = ConsumeResults;
        return SharedThis(this);
    }

    TSharedPtr<FTransactionResult> FTransactionResult::WithAcquireResults(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionResult>>> AcquireResults
    )
    {
        this->AcquireResultsValue = AcquireResults;
        return SharedThis(this);
    }

    TSharedPtr<FTransactionResult> FTransactionResult::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FTransactionResult> FTransactionResult::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FTransactionResult::GetTransactionResultId() const
    {
        return TransactionResultIdValue;
    }
    TOptional<FString> FTransactionResult::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FTransactionResult::GetTransactionId() const
    {
        return TransactionIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FVerifyActionResult>>> FTransactionResult::GetVerifyResults() const
    {
        return VerifyResultsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FConsumeActionResult>>> FTransactionResult::GetConsumeResults() const
    {
        return ConsumeResultsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionResult>>> FTransactionResult::GetAcquireResults() const
    {
        return AcquireResultsValue;
    }
    TOptional<int64> FTransactionResult::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FTransactionResult::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FTransactionResult::GetRevision() const
    {
        return RevisionValue;
    }

    FString FTransactionResult::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FTransactionResult::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):distributor:(?<namespaceName>.+):user:(?<userId>.+):transaction:result:(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FTransactionResult::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):distributor:(?<namespaceName>.+):user:(?<userId>.+):transaction:result:(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FTransactionResult::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):distributor:(?<namespaceName>.+):user:(?<userId>.+):transaction:result:(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FTransactionResult::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):distributor:(?<namespaceName>.+):user:(?<userId>.+):transaction:result:(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FTransactionResult::GetTransactionIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):distributor:(?<namespaceName>.+):user:(?<userId>.+):transaction:result:(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FTransactionResult> FTransactionResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FTransactionResult>()
            ->WithTransactionResultId(Data->HasField(ANSI_TO_TCHAR("transactionResultId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("transactionResultId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTransactionId(Data->HasField(ANSI_TO_TCHAR("transactionId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("transactionId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithVerifyResults(Data->HasField(ANSI_TO_TCHAR("verifyResults")) ? [Data]() -> TSharedPtr<TArray<Model::FVerifyActionResultPtr>>
                {
                    auto v = MakeShared<TArray<Model::FVerifyActionResultPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("verifyResults")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("verifyResults")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("verifyResults")))
                        {
                            v->Add(Model::FVerifyActionResult::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FVerifyActionResultPtr>>())
            ->WithConsumeResults(Data->HasField(ANSI_TO_TCHAR("consumeResults")) ? [Data]() -> TSharedPtr<TArray<Model::FConsumeActionResultPtr>>
                {
                    auto v = MakeShared<TArray<Model::FConsumeActionResultPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("consumeResults")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("consumeResults")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("consumeResults")))
                        {
                            v->Add(Model::FConsumeActionResult::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FConsumeActionResultPtr>>())
            ->WithAcquireResults(Data->HasField(ANSI_TO_TCHAR("acquireResults")) ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionResultPtr>>
                {
                    auto v = MakeShared<TArray<Model::FAcquireActionResultPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("acquireResults")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("acquireResults")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("acquireResults")))
                        {
                            v->Add(Model::FAcquireActionResult::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FAcquireActionResultPtr>>())
            ->WithCreatedAt(Data->HasField(ANSI_TO_TCHAR("createdAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("createdAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField(ANSI_TO_TCHAR("revision")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("revision"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FTransactionResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TransactionResultIdValue.IsSet())
        {
            JsonRootObject->SetStringField("transactionResultId", TransactionResultIdValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (TransactionIdValue.IsSet())
        {
            JsonRootObject->SetStringField("transactionId", TransactionIdValue.GetValue());
        }
        if (VerifyResultsValue != nullptr && VerifyResultsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *VerifyResultsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("verifyResults", v);
        }
        if (ConsumeResultsValue != nullptr && ConsumeResultsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ConsumeResultsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("consumeResults", v);
        }
        if (AcquireResultsValue != nullptr && AcquireResultsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AcquireResultsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("acquireResults", v);
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FTransactionResult::TypeName = "TransactionResult";
}