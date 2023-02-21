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

#include "JobQueue/Model/DeadLetterJob.h"

namespace Gs2::JobQueue::Model
{
    FDeadLetterJob::FDeadLetterJob():
        DeadLetterJobIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ScriptIdValue(TOptional<FString>()),
        ArgsValue(TOptional<FString>()),
        ResultValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>())
    {
    }

    FDeadLetterJob::FDeadLetterJob(
        const FDeadLetterJob& From
    ):
        DeadLetterJobIdValue(From.DeadLetterJobIdValue),
        NameValue(From.NameValue),
        UserIdValue(From.UserIdValue),
        ScriptIdValue(From.ScriptIdValue),
        ArgsValue(From.ArgsValue),
        ResultValue(From.ResultValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue)
    {
    }

    TSharedPtr<FDeadLetterJob> FDeadLetterJob::WithDeadLetterJobId(
        const TOptional<FString> DeadLetterJobId
    )
    {
        this->DeadLetterJobIdValue = DeadLetterJobId;
        return SharedThis(this);
    }

    TSharedPtr<FDeadLetterJob> FDeadLetterJob::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FDeadLetterJob> FDeadLetterJob::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FDeadLetterJob> FDeadLetterJob::WithScriptId(
        const TOptional<FString> ScriptId
    )
    {
        this->ScriptIdValue = ScriptId;
        return SharedThis(this);
    }

    TSharedPtr<FDeadLetterJob> FDeadLetterJob::WithArgs(
        const TOptional<FString> Args
    )
    {
        this->ArgsValue = Args;
        return SharedThis(this);
    }

    TSharedPtr<FDeadLetterJob> FDeadLetterJob::WithResult(
        const TSharedPtr<TArray<TSharedPtr<Model::FJobResultBody>>> Result
    )
    {
        this->ResultValue = Result;
        return SharedThis(this);
    }

    TSharedPtr<FDeadLetterJob> FDeadLetterJob::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FDeadLetterJob> FDeadLetterJob::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FDeadLetterJob::GetDeadLetterJobId() const
    {
        return DeadLetterJobIdValue;
    }
    TOptional<FString> FDeadLetterJob::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FDeadLetterJob::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FDeadLetterJob::GetScriptId() const
    {
        return ScriptIdValue;
    }
    TOptional<FString> FDeadLetterJob::GetArgs() const
    {
        return ArgsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FJobResultBody>>> FDeadLetterJob::GetResult() const
    {
        return ResultValue;
    }
    TOptional<int64> FDeadLetterJob::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FDeadLetterJob::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FDeadLetterJob::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FDeadLetterJob::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    TOptional<FString> FDeadLetterJob::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):queue:(?<namespaceName>.+):user:(?<userId>.+):dead:(?<deadLetterJobName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FDeadLetterJob::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):queue:(?<namespaceName>.+):user:(?<userId>.+):dead:(?<deadLetterJobName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FDeadLetterJob::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):queue:(?<namespaceName>.+):user:(?<userId>.+):dead:(?<deadLetterJobName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FDeadLetterJob::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):queue:(?<namespaceName>.+):user:(?<userId>.+):dead:(?<deadLetterJobName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FDeadLetterJob::GetDeadLetterJobNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):queue:(?<namespaceName>.+):user:(?<userId>.+):dead:(?<deadLetterJobName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FDeadLetterJob> FDeadLetterJob::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeadLetterJob>()
            ->WithDeadLetterJobId(Data->HasField("deadLetterJobId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("deadLetterJobId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("name", v))
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
            ->WithScriptId(Data->HasField("scriptId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("scriptId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithArgs(Data->HasField("args") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("args", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithResult(Data->HasField("result") ? [Data]() -> TSharedPtr<TArray<Model::FJobResultBodyPtr>>
                {
                    auto v = MakeShared<TArray<Model::FJobResultBodyPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("result") && Data->HasTypedField<EJson::Array>("result"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("result"))
                        {
                            v->Add(Model::FJobResultBody::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : nullptr)
            ->WithCreatedAt(Data->HasField("createdAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("createdAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField("updatedAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("updatedAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FDeadLetterJob::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (DeadLetterJobIdValue.IsSet())
        {
            JsonRootObject->SetStringField("deadLetterJobId", DeadLetterJobIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (ScriptIdValue.IsSet())
        {
            JsonRootObject->SetStringField("scriptId", ScriptIdValue.GetValue());
        }
        if (ArgsValue.IsSet())
        {
            JsonRootObject->SetStringField("args", ArgsValue.GetValue());
        }
        if (ResultValue != nullptr && ResultValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ResultValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("result", v);
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FDeadLetterJob::TypeName = "DeadLetterJob";
}