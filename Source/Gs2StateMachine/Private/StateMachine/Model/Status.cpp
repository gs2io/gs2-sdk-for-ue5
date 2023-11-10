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

#include "StateMachine/Model/Status.h"

namespace Gs2::StateMachine::Model
{
    FStatus::FStatus():
        StatusIdValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        StateMachineVersionValue(TOptional<int64>()),
        StacksValue(nullptr),
        VariablesValue(nullptr),
        StatusValue(TOptional<FString>()),
        LastErrorValue(TOptional<FString>()),
        TransitionCountValue(TOptional<int32>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>())
    {
    }

    FStatus::FStatus(
        const FStatus& From
    ):
        StatusIdValue(From.StatusIdValue),
        UserIdValue(From.UserIdValue),
        NameValue(From.NameValue),
        StateMachineVersionValue(From.StateMachineVersionValue),
        StacksValue(From.StacksValue),
        VariablesValue(From.VariablesValue),
        StatusValue(From.StatusValue),
        LastErrorValue(From.LastErrorValue),
        TransitionCountValue(From.TransitionCountValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue)
    {
    }

    TSharedPtr<FStatus> FStatus::WithStatusId(
        const TOptional<FString> StatusId
    )
    {
        this->StatusIdValue = StatusId;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithStateMachineVersion(
        const TOptional<int64> StateMachineVersion
    )
    {
        this->StateMachineVersionValue = StateMachineVersion;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithStacks(
        const TSharedPtr<TArray<TSharedPtr<Model::FStackEntry>>> Stacks
    )
    {
        this->StacksValue = Stacks;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithVariables(
        const TSharedPtr<TArray<TSharedPtr<Model::FVariable>>> Variables
    )
    {
        this->VariablesValue = Variables;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithStatus(
        const TOptional<FString> Status
    )
    {
        this->StatusValue = Status;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithLastError(
        const TOptional<FString> LastError
    )
    {
        this->LastErrorValue = LastError;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithTransitionCount(
        const TOptional<int32> TransitionCount
    )
    {
        this->TransitionCountValue = TransitionCount;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FStatus::GetStatusId() const
    {
        return StatusIdValue;
    }
    TOptional<FString> FStatus::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FStatus::GetName() const
    {
        return NameValue;
    }
    TOptional<int64> FStatus::GetStateMachineVersion() const
    {
        return StateMachineVersionValue;
    }

    FString FStatus::GetStateMachineVersionString() const
    {
        if (!StateMachineVersionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), StateMachineVersionValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Model::FStackEntry>>> FStatus::GetStacks() const
    {
        return StacksValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FVariable>>> FStatus::GetVariables() const
    {
        return VariablesValue;
    }
    TOptional<FString> FStatus::GetStatus() const
    {
        return StatusValue;
    }
    TOptional<FString> FStatus::GetLastError() const
    {
        return LastErrorValue;
    }
    TOptional<int32> FStatus::GetTransitionCount() const
    {
        return TransitionCountValue;
    }

    FString FStatus::GetTransitionCountString() const
    {
        if (!TransitionCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TransitionCountValue.GetValue());
    }
    TOptional<int64> FStatus::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FStatus::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FStatus::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FStatus::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    TOptional<FString> FStatus::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stateMachine:(?<namespaceName>.+):user:(?<userId>.+):status:(?<statusName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStatus::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stateMachine:(?<namespaceName>.+):user:(?<userId>.+):status:(?<statusName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStatus::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stateMachine:(?<namespaceName>.+):user:(?<userId>.+):status:(?<statusName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStatus::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stateMachine:(?<namespaceName>.+):user:(?<userId>.+):status:(?<statusName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStatus::GetStatusNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stateMachine:(?<namespaceName>.+):user:(?<userId>.+):status:(?<statusName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FStatus> FStatus::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FStatus>()
            ->WithStatusId(Data->HasField("statusId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("statusId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("userId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithStateMachineVersion(Data->HasField("stateMachineVersion") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("stateMachineVersion", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithStacks(Data->HasField("stacks") ? [Data]() -> TSharedPtr<TArray<Model::FStackEntryPtr>>
                {
                    auto v = MakeShared<TArray<Model::FStackEntryPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("stacks") && Data->HasTypedField<EJson::Array>("stacks"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("stacks"))
                        {
                            v->Add(Model::FStackEntry::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FStackEntryPtr>>())
            ->WithVariables(Data->HasField("variables") ? [Data]() -> TSharedPtr<TArray<Model::FVariablePtr>>
                {
                    auto v = MakeShared<TArray<Model::FVariablePtr>>();
                    if (!Data->HasTypedField<EJson::Null>("variables") && Data->HasTypedField<EJson::Array>("variables"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("variables"))
                        {
                            v->Add(Model::FVariable::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FVariablePtr>>())
            ->WithStatus(Data->HasField("status") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("status", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithLastError(Data->HasField("lastError") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("lastError", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTransitionCount(Data->HasField("transitionCount") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("transitionCount", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
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

    TSharedPtr<FJsonObject> FStatus::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (StatusIdValue.IsSet())
        {
            JsonRootObject->SetStringField("statusId", StatusIdValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (StateMachineVersionValue.IsSet())
        {
            JsonRootObject->SetStringField("stateMachineVersion", FString::Printf(TEXT("%lld"), StateMachineVersionValue.GetValue()));
        }
        if (StacksValue != nullptr && StacksValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *StacksValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("stacks", v);
        }
        if (VariablesValue != nullptr && VariablesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *VariablesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("variables", v);
        }
        if (StatusValue.IsSet())
        {
            JsonRootObject->SetStringField("status", StatusValue.GetValue());
        }
        if (LastErrorValue.IsSet())
        {
            JsonRootObject->SetStringField("lastError", LastErrorValue.GetValue());
        }
        if (TransitionCountValue.IsSet())
        {
            JsonRootObject->SetNumberField("transitionCount", TransitionCountValue.GetValue());
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

    FString FStatus::TypeName = "Status";
}