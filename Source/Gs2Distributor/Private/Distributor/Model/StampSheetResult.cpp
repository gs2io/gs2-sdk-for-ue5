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
        TaskResultCodesValue(nullptr),
        TaskResultsValue(nullptr),
        SheetResultCodeValue(TOptional<int32>()),
        SheetResultValue(TOptional<FString>()),
        NextTransactionIdValue(TOptional<FString>()),
        CreatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
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
        TaskResultCodesValue(From.TaskResultCodesValue),
        TaskResultsValue(From.TaskResultsValue),
        SheetResultCodeValue(From.SheetResultCodeValue),
        SheetResultValue(From.SheetResultValue),
        NextTransactionIdValue(From.NextTransactionIdValue),
        CreatedAtValue(From.CreatedAtValue),
        RevisionValue(From.RevisionValue)
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

    TSharedPtr<FStampSheetResult> FStampSheetResult::WithTaskResultCodes(
        const TSharedPtr<TArray<int32>> TaskResultCodes
    )
    {
        this->TaskResultCodesValue = TaskResultCodes;
        return SharedThis(this);
    }

    TSharedPtr<FStampSheetResult> FStampSheetResult::WithTaskResults(
        const TSharedPtr<TArray<FString>> TaskResults
    )
    {
        this->TaskResultsValue = TaskResults;
        return SharedThis(this);
    }

    TSharedPtr<FStampSheetResult> FStampSheetResult::WithSheetResultCode(
        const TOptional<int32> SheetResultCode
    )
    {
        this->SheetResultCodeValue = SheetResultCode;
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

    TSharedPtr<FStampSheetResult> FStampSheetResult::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
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
    TSharedPtr<TArray<int32>> FStampSheetResult::GetTaskResultCodes() const
    {
        return TaskResultCodesValue;
    }
    TSharedPtr<TArray<FString>> FStampSheetResult::GetTaskResults() const
    {
        return TaskResultsValue;
    }
    TOptional<int32> FStampSheetResult::GetSheetResultCode() const
    {
        return SheetResultCodeValue;
    }

    FString FStampSheetResult::GetSheetResultCodeString() const
    {
        if (!SheetResultCodeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), SheetResultCodeValue.GetValue());
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
    TOptional<int64> FStampSheetResult::GetRevision() const
    {
        return RevisionValue;
    }

    FString FStampSheetResult::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
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
            ->WithStampSheetResultId(Data->HasField(ANSI_TO_TCHAR("stampSheetResultId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("stampSheetResultId"), v))
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
            ->WithTaskRequests(Data->HasField(ANSI_TO_TCHAR("taskRequests")) ? [Data]() -> TSharedPtr<TArray<Model::FConsumeActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FConsumeActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("taskRequests")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("taskRequests")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("taskRequests")))
                        {
                            v->Add(Model::FConsumeAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FConsumeActionPtr>>())
            ->WithSheetRequest(Data->HasField(ANSI_TO_TCHAR("sheetRequest")) ? [Data]() -> Model::FAcquireActionPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("sheetRequest")))
                    {
                        return nullptr;
                    }
                    return Model::FAcquireAction::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("sheetRequest")));
                 }() : nullptr)
            ->WithTaskResultCodes(Data->HasField(ANSI_TO_TCHAR("taskResultCodes")) ? [Data]() -> TSharedPtr<TArray<int32>>
                {
                    auto v = MakeShared<TArray<int32>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("taskResultCodes")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("taskResultCodes")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("taskResultCodes")))
                        {
                            v->Add(JsonObjectValue->AsNumber());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<int32>>())
            ->WithTaskResults(Data->HasField(ANSI_TO_TCHAR("taskResults")) ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("taskResults")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("taskResults")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("taskResults")))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<FString>>())
            ->WithSheetResultCode(Data->HasField(ANSI_TO_TCHAR("sheetResultCode")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("sheetResultCode"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithSheetResult(Data->HasField(ANSI_TO_TCHAR("sheetResult")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("sheetResult"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithNextTransactionId(Data->HasField(ANSI_TO_TCHAR("nextTransactionId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("nextTransactionId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
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
        if (TaskResultCodesValue != nullptr && TaskResultCodesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *TaskResultCodesValue)
            {
                v.Add(MakeShared<FJsonValueNumber>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("taskResultCodes", v);
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
        if (SheetResultCodeValue.IsSet())
        {
            JsonRootObject->SetNumberField("sheetResultCode", SheetResultCodeValue.GetValue());
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
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FStampSheetResult::TypeName = "StampSheetResult";
}