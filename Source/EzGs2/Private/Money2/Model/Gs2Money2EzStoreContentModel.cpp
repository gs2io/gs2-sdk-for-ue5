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

#include "Money2/Model/Gs2Money2EzStoreContentModel.h"

namespace Gs2::UE5::Money2::Model
{

    TSharedPtr<FEzStoreContentModel> FEzStoreContentModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzStoreContentModel> FEzStoreContentModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzStoreContentModel> FEzStoreContentModel::WithAppleAppStore(
        const TSharedPtr<Gs2::UE5::Money2::Model::FEzAppleAppStoreContent> AppleAppStore
    )
    {
        this->AppleAppStoreValue = AppleAppStore;
        return SharedThis(this);
    }

    TSharedPtr<FEzStoreContentModel> FEzStoreContentModel::WithGooglePlay(
        const TSharedPtr<Gs2::UE5::Money2::Model::FEzGooglePlayContent> GooglePlay
    )
    {
        this->GooglePlayValue = GooglePlay;
        return SharedThis(this);
    }
    TOptional<FString> FEzStoreContentModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzStoreContentModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<Gs2::UE5::Money2::Model::FEzAppleAppStoreContent> FEzStoreContentModel::GetAppleAppStore() const
    {
        return AppleAppStoreValue;
    }
    TSharedPtr<Gs2::UE5::Money2::Model::FEzGooglePlayContent> FEzStoreContentModel::GetGooglePlay() const
    {
        return GooglePlayValue;
    }

    Gs2::Money2::Model::FStoreContentModelPtr FEzStoreContentModel::ToModel() const
    {
        return MakeShared<Gs2::Money2::Model::FStoreContentModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithAppleAppStore(AppleAppStoreValue == nullptr ? nullptr : AppleAppStoreValue->ToModel())
            ->WithGooglePlay(GooglePlayValue == nullptr ? nullptr : GooglePlayValue->ToModel());
    }

    TSharedPtr<FEzStoreContentModel> FEzStoreContentModel::FromModel(const Gs2::Money2::Model::FStoreContentModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzStoreContentModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithAppleAppStore(Model->GetAppleAppStore() != nullptr ? Gs2::UE5::Money2::Model::FEzAppleAppStoreContent::FromModel(Model->GetAppleAppStore()) : nullptr)
            ->WithGooglePlay(Model->GetGooglePlay() != nullptr ? Gs2::UE5::Money2::Model::FEzGooglePlayContent::FromModel(Model->GetGooglePlay()) : nullptr);
    }
}