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

#include "EzGs2/Public/Datastore/Model/Gs2DatastoreEzDataObjectHistory.h"

namespace Gs2::UE5::Datastore::Model
{

    TSharedPtr<FEzDataObjectHistory> FEzDataObjectHistory::WithDataObjectHistoryId(
        const TOptional<FString> DataObjectHistoryId
    )
    {
        this->DataObjectHistoryIdValue = DataObjectHistoryId;
        return SharedThis(this);
    }

    TSharedPtr<FEzDataObjectHistory> FEzDataObjectHistory::WithGeneration(
        const TOptional<FString> Generation
    )
    {
        this->GenerationValue = Generation;
        return SharedThis(this);
    }

    TSharedPtr<FEzDataObjectHistory> FEzDataObjectHistory::WithContentLength(
        const TOptional<int64> ContentLength
    )
    {
        this->ContentLengthValue = ContentLength;
        return SharedThis(this);
    }

    TSharedPtr<FEzDataObjectHistory> FEzDataObjectHistory::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FEzDataObjectHistory::GetDataObjectHistoryId() const
    {
        return DataObjectHistoryIdValue;
    }
    TOptional<FString> FEzDataObjectHistory::GetGeneration() const
    {
        return GenerationValue;
    }
    TOptional<int64> FEzDataObjectHistory::GetContentLength() const
    {
        return ContentLengthValue;
    }

    FString FEzDataObjectHistory::GetContentLengthString() const
    {
        if (!ContentLengthValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ContentLengthValue.GetValue());
    }
    TOptional<int64> FEzDataObjectHistory::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FEzDataObjectHistory::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }

    Gs2::Datastore::Model::FDataObjectHistoryPtr FEzDataObjectHistory::ToModel() const
    {
        return MakeShared<Gs2::Datastore::Model::FDataObjectHistory>()
            ->WithDataObjectHistoryId(DataObjectHistoryIdValue)
            ->WithGeneration(GenerationValue)
            ->WithContentLength(ContentLengthValue)
            ->WithCreatedAt(CreatedAtValue);
    }

    TSharedPtr<FEzDataObjectHistory> FEzDataObjectHistory::FromModel(const Gs2::Datastore::Model::FDataObjectHistoryPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzDataObjectHistory>()
            ->WithDataObjectHistoryId(Model->GetDataObjectHistoryId())
            ->WithGeneration(Model->GetGeneration())
            ->WithContentLength(Model->GetContentLength())
            ->WithCreatedAt(Model->GetCreatedAt());
    }
}