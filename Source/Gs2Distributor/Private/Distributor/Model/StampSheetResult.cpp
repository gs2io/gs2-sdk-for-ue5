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

#include "Distributor/Model/StampSheetResult.h"

namespace Gs2::Distributor::Model
{
    FStampSheetResult::FStampSheetResult():
        StampSheetResultIdValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        TransactionIdValue(TOptional<FString>()),
        TaskRequestsValue(nullptr),
        SheetRequestValue(nullptr),
        TaskResultsValue(nullptr),
        SheetResultValue(TOptional<FString>()),
        NextTransactionIdValue(TOptional<FString>()),
        CreatedAtValue(TOptional<int64>())
    {
    }

    FStampSheetResult::FStampSheetResult(
        const FStampSheetResult& From
    ):
        StampSheetResultIdValue(From.StampSheetResultIdValue),
        UserIdValue(From.UserIdValue),
        TransactionIdValue(From.TransactionIdValue),
        TaskRequestsValue(From.TaskRequestsValue),
        SheetRequestValue(From.SheetRequestValue),
        TaskResultsValue(From.TaskResultsValue),
        SheetResultValue(From.SheetResultValue),
        NextTransactionIdValue(From.NextTransactionIdValue),
        CreatedAtValue(From.CreatedAtValue)
    {
    }

    TSharedPtr<FStampSheetResult> FStampSheetResult::WithStampSheetResultId(
        const TOptional<FString> StampSheetResultId
    )
    {
        this->StampSheetResultIdValue = StampSheetResultId;
        return SharedThis(this);
    }

    TSharedPtr<FStampSheetResult> FStampSheetResult::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FStampSheetResult> FStampSheetResult::WithTransactionId(
        const TOptional<FString> TransactionId
    )
    {
        this->TransactionIdValue = TransactionId;
        return SharedThis(this);
    }

    TSharedPtr<FStampSheetResult> FStampSheetResult::WithTaskRequests(
        const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> TaskRequests
    )
    {
        this->TaskRequestsValue = TaskRequests;
        return SharedThis(this);
    }

    TSharedPtr<FStampSheetResult> FStampSheetResult::WithSheetRequest(
        const TSharedPtr<FAcquireAction> SheetRequest
    )
    {
        this->SheetRequestValue = SheetRequest;
        return SharedThis(this);
    }

    TSharedPtr<FStampSheetResult> FStampSheetResult::WithTaskResults(
        const TSharedPtr<TArray<FString>> TaskResults
    )
    {
        this->TaskResultsValue = TaskResults;
        return SharedThis(this);
    }

    TSharedPtr<FStampSheetResult> FStampSheetResult::WithSheetResult(
        const TOptional<FString> SheetResult
    )
    {
        this->SheetResultValue = SheetResult;
        return SharedThis(this);
    }

    TSharedPtr<FStampSheetResult> FStampSheetResult::WithNextTransactionId(
        const TOptional<FString> NextTransactionId
    )
    {
        this->NextTransactionIdValue = NextTransactionId;
        return SharedThis(this);
    }

    TSharedPtr<FStampSheetResult> FStampSheetResult::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FStampSheetResult::GetStampSheetResultId() const
    {
        return StampSheetResultIdValue;
    }
    TOptional<FString> FStampSheetResult::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FStampSheetResult::GetTransactionId() const
    {
        return TransactionIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> FStampSheetResult::GetTaskRequests() const
    {
        return TaskRequestsValue;
    }
    TSharedPtr<FAcquireAction> FStampSheetResult::GetSheetRequest() const
    {
        return SheetRequestValue;
    }
    TSharedPtr<TArray<FString>> FStampSheetResult::GetTaskResults() const
    {
        return TaskResultsValue;
    }
    TOptional<FString> FStampSheetResult::GetSheetResult() const
    {
        return SheetResultValue;
    }
    TOptional<FString> FStampSheetResult::GetNextTransactionId() const
    {
        return NextTransactionIdValue;
    }
    TOptional<int64> FStampSheetResult::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FStampSheetResult::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }

    TOptional<FString> FStampSheetResult::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):distributor:(?<namespaceName>.+):user:(?<userId>.+):stampSheet:result:(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStampSheetResult::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):distributor:(?<namespaceName>.+):user:(?<userId>.+):stampSheet:result:(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStampSheetResult::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):distributor:(?<namespaceName>.+):user:(?<userId>.+):stampSheet:result:(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStampSheetResult::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):distributor:(?<namespaceName>.+):user:(?<userId>.+):stampSheet:result:(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStampSheetResult::GetTransactionIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):distributor:(?<namespaceName>.+):user:(?<userId>.+):stampSheet:result:(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FStampSheetResult> FStampSheetResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FStampSheetResult>()
            ->WithStampSheetResultId(Data->HasField("stampSheetResultId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("stampSheetResultId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("userId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTransactionId(Data->HasField("transactionId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("transactionId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTaskRequests(Data->HasField("taskRequests") ? [Data]() -> TSharedPtr<TArray<Model::FConsumeActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FConsumeActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("taskRequests") && Data->HasTypedField<EJson::Array>("taskRequests"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("taskRequests"))
                        {
                            v->Add(Model::FConsumeAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : nullptr)
            ->WithSheetRequest(Data->HasField("sheetRequest") ? [Data]() -> Model::FAcquireActionPtr
                {
                    if (Data->HasTypedField<EJson::Null>("sheetRequest"))
                    {
                        return nullptr;
                    }
                    return Model::FAcquireAction::FromJson(Data->GetObjectField("sheetRequest"));
                 }() : nullptr)
            ->WithTaskResults(Data->HasField("taskResults") ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>("taskResults") && Data->HasTypedField<EJson::Array>("taskResults"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("taskResults"))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : nullptr)
            ->WithSheetResult(Data->HasField("sheetResult") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("sheetResult", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithNextTransactionId(Data->HasField("nextTransactionId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("nextTransactionId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCreatedAt(Data->HasField("createdAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("createdAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FStampSheetResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (StampSheetResultIdValue.IsSet())
        {
            JsonRootObject->SetStringField("stampSheetResultId", StampSheetResultIdValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (TransactionIdValue.IsSet())
        {
            JsonRootObject->SetStringField("transactionId", TransactionIdValue.GetValue());
        }
        if (TaskRequestsValue != nullptr && TaskRequestsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *TaskRequestsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("taskRequests", v);
        }
        if (SheetRequestValue != nullptr && SheetRequestValue.IsValid())
        {
            JsonRootObject->SetObjectField("sheetRequest", SheetRequestValue->ToJson());
        }
        if (TaskResultsValue != nullptr && TaskResultsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *TaskResultsValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("taskResults", v);
        }
        if (SheetResultValue.IsSet())
        {
            JsonRootObject->SetStringField("sheetResult", SheetResultValue.GetValue());
        }
        if (NextTransactionIdValue.IsSet())
        {
            JsonRootObject->SetStringField("nextTransactionId", NextTransactionIdValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FStampSheetResult::TypeName = "StampSheetResult";
}