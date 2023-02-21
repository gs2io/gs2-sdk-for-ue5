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

#include "EzGs2/Public/Quest/Model/Gs2QuestEzContents.h"

namespace Gs2::UE5::Quest::Model
{

    TSharedPtr<FEzContents> FEzContents::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzContents> FEzContents::WithCompleteAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzAcquireAction>>> CompleteAcquireActions
    )
    {
        this->CompleteAcquireActionsValue = CompleteAcquireActions;
        return SharedThis(this);
    }
    TOptional<FString> FEzContents::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzAcquireAction>>> FEzContents::GetCompleteAcquireActions() const
    {
        return CompleteAcquireActionsValue;
    }

    Gs2::Quest::Model::FContentsPtr FEzContents::ToModel() const
    {
        return MakeShared<Gs2::Quest::Model::FContents>()
            ->WithMetadata(MetadataValue)
            ->WithCompleteAcquireActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Quest::Model::FAcquireAction>>>();
                    if (CompleteAcquireActionsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *CompleteAcquireActionsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzContents> FEzContents::FromModel(const Gs2::Quest::Model::FContentsPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzContents>()
            ->WithMetadata(Model->GetMetadata())
            ->WithCompleteAcquireActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzAcquireAction>>>();
                    if (Model->GetCompleteAcquireActions() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetCompleteAcquireActions())
                    {
                        v->Add(FEzAcquireAction::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}