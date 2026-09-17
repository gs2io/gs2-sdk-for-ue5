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

#pragma once

#include "Core/Domain/CacheDatabase.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "SerialKey/Model/Cache/CampaignModel.h"
#include "SerialKey/Model/Cache/SerialKey.h"
#include "SerialKey/Model/SerialKey.h"

namespace Gs2::SerialKey::Domain::SpeculativeExecutor::Private
{
    class FSerialKeySpeculativeCommit final
    {
        using FSerialKeyPtr = Gs2::SerialKey::Model::FSerialKeyPtr;
        using FTransform = TFunction<FSerialKeyPtr(const FSerialKeyPtr&)>;

        const Gs2::Core::Domain::FCacheDatabasePtr Cache;
        const TOptional<FString> NamespaceName;
        const FString UserId;
        const FString Code;
        const TOptional<int32> TimeOffset;
        const FString ExpectedSerialKeyId;
        const FTransform Transform;

        bool IsExpected(const FSerialKeyPtr& Item) const
        {
            return Item.IsValid() && Item->GetSerialKeyId().IsSet() &&
                Item->GetSerialKeyId().Get(FString()) == ExpectedSerialKeyId &&
                Item->GetCode().IsSet() && Item->GetCode().Get(FString()) == Code;
        }

    public:
        FSerialKeySpeculativeCommit(
            const Gs2::Core::Domain::FCacheDatabasePtr& InCache,
            const TOptional<FString>& InNamespaceName,
            const FString& InUserId,
            const FString& InCode,
            const TOptional<int32>& InTimeOffset,
            const FString& InExpectedSerialKeyId,
            const FTransform& InTransform
        ):
            Cache(InCache), NamespaceName(InNamespaceName), UserId(InUserId), Code(InCode),
            TimeOffset(InTimeOffset), ExpectedSerialKeyId(InExpectedSerialKeyId), Transform(InTransform)
        {
        }

        FString CompositionKey() const
        {
            return FString::Printf(TEXT("serialKey:%s:SerialKey:%s"), *NamespaceName.Get(FString()), *Code);
        }

        bool TryCompose(
            const TSharedPtr<void>& Current,
            const bool HasCurrent,
            TSharedPtr<void>& Next
        ) const
        {
            try
            {
                Gs2::SerialKey::Model::FCampaignModelPtr Campaign;
                if (!Gs2::SerialKey::Model::Cache::FCampaignModelCache::TryGet(
                    Cache, NamespaceName, Code, TOptional<int32>(), &Campaign
                ) || Campaign.IsValid())
                {
                    Next = nullptr;
                    return false;
                }

                FSerialKeyPtr Source;
                if (HasCurrent)
                {
                    Source = StaticCastSharedPtr<Gs2::SerialKey::Model::FSerialKey>(Current);
                }
                else if (!Gs2::SerialKey::Model::Cache::FSerialKeyCache::TryGet(
                    Cache, NamespaceName, UserId, Code, TimeOffset, &Source
                ))
                {
                    Next = nullptr;
                    return false;
                }
                if (!IsExpected(Source))
                {
                    Next = nullptr;
                    return false;
                }

                const FSerialKeyPtr Changed = Transform(Source);
                if (!IsExpected(Changed))
                {
                    Next = nullptr;
                    return false;
                }
                Next = Changed;
                return true;
            }
            catch (...)
            {
                Next = nullptr;
                return false;
            }
        }

        void Commit(const TSharedPtr<void>& State) const
        {
            try
            {
                const FSerialKeyPtr Changed = StaticCastSharedPtr<Gs2::SerialKey::Model::FSerialKey>(State);
                if (!IsExpected(Changed)) return;

                FSerialKeyPtr Live;
                if (!Gs2::SerialKey::Model::Cache::FSerialKeyCache::TryGet(
                    Cache, NamespaceName, UserId, Code, TimeOffset, &Live
                ) || !IsExpected(Live)) return;

                Gs2::SerialKey::Model::Cache::FSerialKeyCache::Put(
                    Cache, NamespaceName, UserId, Code, TimeOffset, Changed
                );
            }
            catch (...)
            {
            }
        }
    };
}
