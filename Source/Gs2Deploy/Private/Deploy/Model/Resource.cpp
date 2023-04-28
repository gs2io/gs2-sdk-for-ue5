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

#include "Deploy/Model/Resource.h"

namespace Gs2::Deploy::Model
{
    FResource::FResource():
        ResourceIdValue(TOptional<FString>()),
        TypeValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        RequestValue(TOptional<FString>()),
        ResponseValue(TOptional<FString>()),
        RollbackContextValue(TOptional<FString>()),
        RollbackRequestValue(TOptional<FString>()),
        RollbackAfterValue(nullptr),
        OutputFieldsValue(nullptr),
        WorkIdValue(TOptional<FString>()),
        CreatedAtValue(TOptional<int64>())
    {
    }

    FResource::FResource(
        const FResource& From
    ):
        ResourceIdValue(From.ResourceIdValue),
        TypeValue(From.TypeValue),
        NameValue(From.NameValue),
        RequestValue(From.RequestValue),
        ResponseValue(From.ResponseValue),
        RollbackContextValue(From.RollbackContextValue),
        RollbackRequestValue(From.RollbackRequestValue),
        RollbackAfterValue(From.RollbackAfterValue),
        OutputFieldsValue(From.OutputFieldsValue),
        WorkIdValue(From.WorkIdValue),
        CreatedAtValue(From.CreatedAtValue)
    {
    }

    TSharedPtr<FResource> FResource::WithResourceId(
        const TOptional<FString> ResourceId
    )
    {
        this->ResourceIdValue = ResourceId;
        return SharedThis(this);
    }

    TSharedPtr<FResource> FResource::WithType(
        const TOptional<FString> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FResource> FResource::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FResource> FResource::WithRequest(
        const TOptional<FString> Request
    )
    {
        this->RequestValue = Request;
        return SharedThis(this);
    }

    TSharedPtr<FResource> FResource::WithResponse(
        const TOptional<FString> Response
    )
    {
        this->ResponseValue = Response;
        return SharedThis(this);
    }

    TSharedPtr<FResource> FResource::WithRollbackContext(
        const TOptional<FString> RollbackContext
    )
    {
        this->RollbackContextValue = RollbackContext;
        return SharedThis(this);
    }

    TSharedPtr<FResource> FResource::WithRollbackRequest(
        const TOptional<FString> RollbackRequest
    )
    {
        this->RollbackRequestValue = RollbackRequest;
        return SharedThis(this);
    }

    TSharedPtr<FResource> FResource::WithRollbackAfter(
        const TSharedPtr<TArray<FString>> RollbackAfter
    )
    {
        this->RollbackAfterValue = RollbackAfter;
        return SharedThis(this);
    }

    TSharedPtr<FResource> FResource::WithOutputFields(
        const TSharedPtr<TArray<TSharedPtr<Model::FOutputField>>> OutputFields
    )
    {
        this->OutputFieldsValue = OutputFields;
        return SharedThis(this);
    }

    TSharedPtr<FResource> FResource::WithWorkId(
        const TOptional<FString> WorkId
    )
    {
        this->WorkIdValue = WorkId;
        return SharedThis(this);
    }

    TSharedPtr<FResource> FResource::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FResource::GetResourceId() const
    {
        return ResourceIdValue;
    }
    TOptional<FString> FResource::GetType() const
    {
        return TypeValue;
    }
    TOptional<FString> FResource::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FResource::GetRequest() const
    {
        return RequestValue;
    }
    TOptional<FString> FResource::GetResponse() const
    {
        return ResponseValue;
    }
    TOptional<FString> FResource::GetRollbackContext() const
    {
        return RollbackContextValue;
    }
    TOptional<FString> FResource::GetRollbackRequest() const
    {
        return RollbackRequestValue;
    }
    TSharedPtr<TArray<FString>> FResource::GetRollbackAfter() const
    {
        return RollbackAfterValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FOutputField>>> FResource::GetOutputFields() const
    {
        return OutputFieldsValue;
    }
    TOptional<FString> FResource::GetWorkId() const
    {
        return WorkIdValue;
    }
    TOptional<int64> FResource::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FResource::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }

    TOptional<FString> FResource::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):deploy:(?<stackName>.+):resource:(?<resourceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FResource::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):deploy:(?<stackName>.+):resource:(?<resourceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FResource::GetStackNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):deploy:(?<stackName>.+):resource:(?<resourceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FResource::GetResourceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):deploy:(?<stackName>.+):resource:(?<resourceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FResource> FResource::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FResource>()
            ->WithResourceId(Data->HasField("resourceId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("resourceId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithType(Data->HasField("type") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("type", v))
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
            ->WithRequest(Data->HasField("request") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("request", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithResponse(Data->HasField("response") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("response", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRollbackContext(Data->HasField("rollbackContext") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("rollbackContext", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRollbackRequest(Data->HasField("rollbackRequest") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("rollbackRequest", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRollbackAfter(Data->HasField("rollbackAfter") ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>("rollbackAfter") && Data->HasTypedField<EJson::Array>("rollbackAfter"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("rollbackAfter"))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<FString>>())
            ->WithOutputFields(Data->HasField("outputFields") ? [Data]() -> TSharedPtr<TArray<Model::FOutputFieldPtr>>
                {
                    auto v = MakeShared<TArray<Model::FOutputFieldPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("outputFields") && Data->HasTypedField<EJson::Array>("outputFields"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("outputFields"))
                        {
                            v->Add(Model::FOutputField::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FOutputFieldPtr>>())
            ->WithWorkId(Data->HasField("workId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("workId", v))
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

    TSharedPtr<FJsonObject> FResource::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ResourceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("resourceId", ResourceIdValue.GetValue());
        }
        if (TypeValue.IsSet())
        {
            JsonRootObject->SetStringField("type", TypeValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (RequestValue.IsSet())
        {
            JsonRootObject->SetStringField("request", RequestValue.GetValue());
        }
        if (ResponseValue.IsSet())
        {
            JsonRootObject->SetStringField("response", ResponseValue.GetValue());
        }
        if (RollbackContextValue.IsSet())
        {
            JsonRootObject->SetStringField("rollbackContext", RollbackContextValue.GetValue());
        }
        if (RollbackRequestValue.IsSet())
        {
            JsonRootObject->SetStringField("rollbackRequest", RollbackRequestValue.GetValue());
        }
        if (RollbackAfterValue != nullptr && RollbackAfterValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *RollbackAfterValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("rollbackAfter", v);
        }
        if (OutputFieldsValue != nullptr && OutputFieldsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *OutputFieldsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("outputFields", v);
        }
        if (WorkIdValue.IsSet())
        {
            JsonRootObject->SetStringField("workId", WorkIdValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FResource::TypeName = "Resource";
}