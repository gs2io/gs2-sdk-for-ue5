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

#include "Deploy/Model/ChangeSet.h"

namespace Gs2::Deploy::Model
{
    FChangeSet::FChangeSet():
        ResourceNameValue(TOptional<FString>()),
        ResourceTypeValue(TOptional<FString>()),
        OperationValue(TOptional<FString>())
    {
    }

    FChangeSet::FChangeSet(
        const FChangeSet& From
    ):
        ResourceNameValue(From.ResourceNameValue),
        ResourceTypeValue(From.ResourceTypeValue),
        OperationValue(From.OperationValue)
    {
    }

    TSharedPtr<FChangeSet> FChangeSet::WithResourceName(
        const TOptional<FString> ResourceName
    )
    {
        this->ResourceNameValue = ResourceName;
        return SharedThis(this);
    }

    TSharedPtr<FChangeSet> FChangeSet::WithResourceType(
        const TOptional<FString> ResourceType
    )
    {
        this->ResourceTypeValue = ResourceType;
        return SharedThis(this);
    }

    TSharedPtr<FChangeSet> FChangeSet::WithOperation(
        const TOptional<FString> Operation
    )
    {
        this->OperationValue = Operation;
        return SharedThis(this);
    }
    TOptional<FString> FChangeSet::GetResourceName() const
    {
        return ResourceNameValue;
    }
    TOptional<FString> FChangeSet::GetResourceType() const
    {
        return ResourceTypeValue;
    }
    TOptional<FString> FChangeSet::GetOperation() const
    {
        return OperationValue;
    }

    TSharedPtr<FChangeSet> FChangeSet::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FChangeSet>()
            ->WithResourceName(Data->HasField("resourceName") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("resourceName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithResourceType(Data->HasField("resourceType") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("resourceType", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithOperation(Data->HasField("operation") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("operation", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FChangeSet::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ResourceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("resourceName", ResourceNameValue.GetValue());
        }
        if (ResourceTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("resourceType", ResourceTypeValue.GetValue());
        }
        if (OperationValue.IsSet())
        {
            JsonRootObject->SetStringField("operation", OperationValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FChangeSet::TypeName = "ChangeSet";
}