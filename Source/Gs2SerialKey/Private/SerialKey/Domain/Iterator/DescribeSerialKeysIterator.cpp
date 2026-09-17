
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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

// ReSharper disable CppUnusedIncludeDirective

#include "SerialKey/Domain/Iterator/DescribeSerialKeysIterator.h"
#include "SerialKey/Domain/Model/SerialKey.h"
#include "SerialKey/Domain/Model/User.h"

#include "Core/Domain/Gs2.h"

#include "SerialKey/Model/Cache/SerialKey.h"

namespace Gs2::SerialKey::Domain::Iterator
{

    FDescribeSerialKeysIterator::FDescribeSerialKeysIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::SerialKey::FGs2SerialKeyRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> CampaignModelName,
        const TOptional<FString> IssueJobName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName),
        CampaignModelName(CampaignModelName),
        IssueJobName(IssueJobName)
    {
    }

    FDescribeSerialKeysIterator::FDescribeSerialKeysIterator(
        const FDescribeSerialKeysIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        CampaignModelName(From.CampaignModelName),
        IssueJobName(From.IssueJobName)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeSerialKeysIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::SerialKey::Model::FSerialKey>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeSerialKeysIterator::FIterator::FIterator(
        const TSharedRef<FDescribeSerialKeysIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeSerialKeysIterator::FIterator& FDescribeSerialKeysIterator::FIterator::operator++()
    {


        if (bEnd) return *this;

        if (ErrorValue && bLast)
        {
            bEnd = true;
            return *this;
        }

        if (RangeIteratorOpt && *RangeIteratorOpt) ++*RangeIteratorOpt;

        // Keep the previous page alive until its iterator has been replaced.
        const auto PreviousRange = Range;
        if (!RangeIteratorOpt || (!*RangeIteratorOpt && !bLast))
        {
            const auto ListParentKey = Gs2::SerialKey::Model::Cache::FSerialKeyCache::CreateCacheParentKey(
                Self->NamespaceName,
                TOptional<FString>(),
                TOptional<int32>()
            );
            if (!RangeIteratorOpt && (!Self->IssueJobName.IsSet()))
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::SerialKey::Model::FSerialKey>(ListParentKey);

                if (Range)
                {
                    Range->RemoveAll([this](const Gs2::SerialKey::Model::FSerialKeyPtr& Item) { return Self->CampaignModelName && Item->GetCampaignModelName() != Self->CampaignModelName; });
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    PageToken = TOptional<FString>();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }
            const auto Request =
                MakeShared<Gs2::SerialKey::Request::FDescribeSerialKeysRequest>()
                    ->WithContextStack(Self->Gs2->DefaultContextStack)
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithCampaignModelName(Self->CampaignModelName)
                    ->WithIssueJobName(Self->IssueJobName)
                    ->WithPageToken(PageToken)
                    ->WithLimit(FetchSize)
            ;
            const auto Future = Self->Client->DescribeSerialKeys(Request);
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                ErrorValue = Future->GetTask().Error();
                bLast = true;
                return *this;
            }
            else
            {
                ErrorValue = nullptr;
            }
            const auto R = Future->GetTask().Result();
            Future->EnsureCompletion();
            Range = R->GetItems().IsValid() ? R->GetItems() : MakeShared<TArray<Gs2::SerialKey::Model::FSerialKeyPtr>>();
            const auto ResultModel = R;


            if (Range.IsValid())
            {
                for (const auto& Item : *Range)
                {
                    if (!Item.IsValid()) continue;
                    Gs2::SerialKey::Model::Cache::FSerialKeyCache::Put(
                        Self->Gs2->Cache,
                        Request->GetNamespaceName(), TOptional<FString>(), Item->GetCode(),
                        TOptional<int32>(), Item
                    );
                }
            }
            if (Range)
            {
                Range->RemoveAll([this](const Gs2::SerialKey::Model::FSerialKeyPtr& Item) { return Self->CampaignModelName && Item->GetCampaignModelName() != Self->CampaignModelName; });
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
            if (bLast && (!Self->IssueJobName.IsSet())) {
                Self->Gs2->Cache->SetListCached(
                    Gs2::SerialKey::Model::FSerialKey::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeSerialKeysIterator::FIterator FDescribeSerialKeysIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeSerialKeysIterator::FIterator FDescribeSerialKeysIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeSerialKeysIterator::FIterator FDescribeSerialKeysIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

