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

#include "EzGs2/Public/JobQueue/Model/Gs2JobQueueEzJobEntry.h"

namespace Gs2::UE5::JobQueue::Model
{

    TSharedPtr<FEzJobEntry> FEzJobEntry::WithScriptId(
        const TOptional<FString> ScriptId
    )
    {
        this->ScriptIdValue = ScriptId;
        return SharedThis(this);
    }

    TSharedPtr<FEzJobEntry> FEzJobEntry::WithArgs(
        const TOptional<FString> Args
    )
    {
        this->ArgsValue = Args;
        return SharedThis(this);
    }

    TSharedPtr<FEzJobEntry> FEzJobEntry::WithMaxTryCount(
        const TOptional<int32> MaxTryCount
    )
    {
        this->MaxTryCountValue = MaxTryCount;
        return SharedThis(this);
    }
    TOptional<FString> FEzJobEntry::GetScriptId() const
    {
        return ScriptIdValue;
    }
    TOptional<FString> FEzJobEntry::GetArgs() const
    {
        return ArgsValue;
    }
    TOptional<int32> FEzJobEntry::GetMaxTryCount() const
    {
        return MaxTryCountValue;
    }

    FString FEzJobEntry::GetMaxTryCountString() const
    {
        if (!MaxTryCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaxTryCountValue.GetValue());
    }

    Gs2::JobQueue::Model::FJobEntryPtr FEzJobEntry::ToModel() const
    {
        return MakeShared<Gs2::JobQueue::Model::FJobEntry>()
            ->WithScriptId(ScriptIdValue)
            ->WithArgs(ArgsValue)
            ->WithMaxTryCount(MaxTryCountValue);
    }

    TSharedPtr<FEzJobEntry> FEzJobEntry::FromModel(const Gs2::JobQueue::Model::FJobEntryPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzJobEntry>()
            ->WithScriptId(Model->GetScriptId())
            ->WithArgs(Model->GetArgs())
            ->WithMaxTryCount(Model->GetMaxTryCount());
    }
}