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

#include "Datastore/Model/DataObject.h"

namespace Gs2::Datastore::Model
{
    FDataObject::FDataObject():
        DataObjectIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ScopeValue(TOptional<FString>()),
        AllowUserIdsValue(nullptr),
        StatusValue(TOptional<FString>()),
        GenerationValue(TOptional<FString>()),
        PreviousGenerationValue(TOptional<FString>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>())
    {
    }

    FDataObject::FDataObject(
        const FDataObject& From
    ):
        DataObjectIdValue(From.DataObjectIdValue),
        NameValue(From.NameValue),
        UserIdValue(From.UserIdValue),
        ScopeValue(From.ScopeValue),
        AllowUserIdsValue(From.AllowUserIdsValue),
        StatusValue(From.StatusValue),
        GenerationValue(From.GenerationValue),
        PreviousGenerationValue(From.PreviousGenerationValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue)
    {
    }

    TSharedPtr<FDataObject> FDataObject::WithDataObjectId(
        const TOptional<FString> DataObjectId
    )
    {
        this->DataObjectIdValue = DataObjectId;
        return SharedThis(this);
    }

    TSharedPtr<FDataObject> FDataObject::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FDataObject> FDataObject::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FDataObject> FDataObject::WithScope(
        const TOptional<FString> Scope
    )
    {
        this->ScopeValue = Scope;
        return SharedThis(this);
    }

    TSharedPtr<FDataObject> FDataObject::WithAllowUserIds(
        const TSharedPtr<TArray<FString>> AllowUserIds
    )
    {
        this->AllowUserIdsValue = AllowUserIds;
        return SharedThis(this);
    }

    TSharedPtr<FDataObject> FDataObject::WithStatus(
        const TOptional<FString> Status
    )
    {
        this->StatusValue = Status;
        return SharedThis(this);
    }

    TSharedPtr<FDataObject> FDataObject::WithGeneration(
        const TOptional<FString> Generation
    )
    {
        this->GenerationValue = Generation;
        return SharedThis(this);
    }

    TSharedPtr<FDataObject> FDataObject::WithPreviousGeneration(
        const TOptional<FString> PreviousGeneration
    )
    {
        this->PreviousGenerationValue = PreviousGeneration;
        return SharedThis(this);
    }

    TSharedPtr<FDataObject> FDataObject::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FDataObject> FDataObject::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FDataObject::GetDataObjectId() const
    {
        return DataObjectIdValue;
    }
    TOptional<FString> FDataObject::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FDataObject::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FDataObject::GetScope() const
    {
        return ScopeValue;
    }
    TSharedPtr<TArray<FString>> FDataObject::GetAllowUserIds() const
    {
        return AllowUserIdsValue;
    }
    TOptional<FString> FDataObject::GetStatus() const
    {
        return StatusValue;
    }
    TOptional<FString> FDataObject::GetGeneration() const
    {
        return GenerationValue;
    }
    TOptional<FString> FDataObject::GetPreviousGeneration() const
    {
        return PreviousGenerationValue;
    }
    TOptional<int64> FDataObject::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FDataObject::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FDataObject::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FDataObject::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    TOptional<FString> FDataObject::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):datastore:(?<namespaceName>.+):user:(?<userId>.+):data:(?<dataObjectName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FDataObject::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):datastore:(?<namespaceName>.+):user:(?<userId>.+):data:(?<dataObjectName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FDataObject::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):datastore:(?<namespaceName>.+):user:(?<userId>.+):data:(?<dataObjectName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FDataObject::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):datastore:(?<namespaceName>.+):user:(?<userId>.+):data:(?<dataObjectName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FDataObject::GetDataObjectNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):datastore:(?<namespaceName>.+):user:(?<userId>.+):data:(?<dataObjectName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FDataObject> FDataObject::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDataObject>()
            ->WithDataObjectId(Data->HasField("dataObjectId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("dataObjectId", v))
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
            ->WithScope(Data->HasField("scope") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("scope", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAllowUserIds(Data->HasField("allowUserIds") ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>("allowUserIds") && Data->HasTypedField<EJson::Array>("allowUserIds"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("allowUserIds"))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<FString>>())
            ->WithStatus(Data->HasField("status") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("status", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithGeneration(Data->HasField("generation") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("generation", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPreviousGeneration(Data->HasField("previousGeneration") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("previousGeneration", v))
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

    TSharedPtr<FJsonObject> FDataObject::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (DataObjectIdValue.IsSet())
        {
            JsonRootObject->SetStringField("dataObjectId", DataObjectIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (ScopeValue.IsSet())
        {
            JsonRootObject->SetStringField("scope", ScopeValue.GetValue());
        }
        if (AllowUserIdsValue != nullptr && AllowUserIdsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AllowUserIdsValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("allowUserIds", v);
        }
        if (StatusValue.IsSet())
        {
            JsonRootObject->SetStringField("status", StatusValue.GetValue());
        }
        if (GenerationValue.IsSet())
        {
            JsonRootObject->SetStringField("generation", GenerationValue.GetValue());
        }
        if (PreviousGenerationValue.IsSet())
        {
            JsonRootObject->SetStringField("previousGeneration", PreviousGenerationValue.GetValue());
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

    FString FDataObject::TypeName = "DataObject";
}