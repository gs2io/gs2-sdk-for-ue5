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

#include "EzGs2/Public/Datastore/Model/Gs2DatastoreEzDataObject.h"

namespace Gs2::UE5::Datastore::Model
{

    TSharedPtr<FEzDataObject> FEzDataObject::WithDataObjectId(
        const TOptional<FString> DataObjectId
    )
    {
        this->DataObjectIdValue = DataObjectId;
        return SharedThis(this);
    }

    TSharedPtr<FEzDataObject> FEzDataObject::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzDataObject> FEzDataObject::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzDataObject> FEzDataObject::WithScope(
        const TOptional<FString> Scope
    )
    {
        this->ScopeValue = Scope;
        return SharedThis(this);
    }

    TSharedPtr<FEzDataObject> FEzDataObject::WithAllowUserIds(
        const TSharedPtr<TArray<FString>> AllowUserIds
    )
    {
        this->AllowUserIdsValue = AllowUserIds;
        return SharedThis(this);
    }

    TSharedPtr<FEzDataObject> FEzDataObject::WithStatus(
        const TOptional<FString> Status
    )
    {
        this->StatusValue = Status;
        return SharedThis(this);
    }

    TSharedPtr<FEzDataObject> FEzDataObject::WithGeneration(
        const TOptional<FString> Generation
    )
    {
        this->GenerationValue = Generation;
        return SharedThis(this);
    }

    TSharedPtr<FEzDataObject> FEzDataObject::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FEzDataObject> FEzDataObject::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FEzDataObject::GetDataObjectId() const
    {
        return DataObjectIdValue;
    }
    TOptional<FString> FEzDataObject::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzDataObject::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FEzDataObject::GetScope() const
    {
        return ScopeValue;
    }
    TSharedPtr<TArray<FString>> FEzDataObject::GetAllowUserIds() const
    {
        return AllowUserIdsValue;
    }
    TOptional<FString> FEzDataObject::GetStatus() const
    {
        return StatusValue;
    }
    TOptional<FString> FEzDataObject::GetGeneration() const
    {
        return GenerationValue;
    }
    TOptional<int64> FEzDataObject::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FEzDataObject::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FEzDataObject::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FEzDataObject::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    Gs2::Datastore::Model::FDataObjectPtr FEzDataObject::ToModel() const
    {
        return MakeShared<Gs2::Datastore::Model::FDataObject>()
            ->WithDataObjectId(DataObjectIdValue)
            ->WithName(NameValue)
            ->WithUserId(UserIdValue)
            ->WithScope(ScopeValue)
            ->WithAllowUserIds(AllowUserIdsValue)
            ->WithStatus(StatusValue)
            ->WithGeneration(GenerationValue)
            ->WithCreatedAt(CreatedAtValue)
            ->WithUpdatedAt(UpdatedAtValue);
    }

    TSharedPtr<FEzDataObject> FEzDataObject::FromModel(const Gs2::Datastore::Model::FDataObjectPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzDataObject>()
            ->WithDataObjectId(Model->GetDataObjectId())
            ->WithName(Model->GetName())
            ->WithUserId(Model->GetUserId())
            ->WithScope(Model->GetScope())
            ->WithAllowUserIds(Model->GetAllowUserIds())
            ->WithStatus(Model->GetStatus())
            ->WithGeneration(Model->GetGeneration())
            ->WithCreatedAt(Model->GetCreatedAt())
            ->WithUpdatedAt(Model->GetUpdatedAt());
    }
}