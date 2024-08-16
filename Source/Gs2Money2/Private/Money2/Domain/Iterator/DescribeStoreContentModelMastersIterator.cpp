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

#include "Money2/Domain/Iterator/DescribeStoreContentModelMastersIterator.h"
#include "Money2/Domain/Model/StoreContentModelMaster.h"
#include "Money2/Domain/Model/Namespace.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Money2::Domain::Iterator
{

    FDescribeStoreContentModelMastersIterator::FDescribeStoreContentModelMastersIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Money2::FGs2Money2RestClientPtr Client,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName)
    {
    }

    FDescribeStoreContentModelMastersIterator::FDescribeStoreContentModelMastersIterator(
        const FDescribeStoreContentModelMastersIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeStoreContentModelMastersIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Money2::Model::FStoreContentModelMaster>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeStoreContentModelMastersIterator::FIterator::FIterator(
        const TSharedRef<FDescribeStoreContentModelMastersIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeStoreContentModelMastersIterator::FIterator& FDescribeStoreContentModelMastersIterator::FIterator::operator++()
    {
        

        if (bEnd) return *this;

        if (ErrorValue && bLast)
        {
            bEnd = true;
            return *this;
        }

        if (RangeIteratorOpt) ++*RangeIteratorOpt;

        if (!RangeIteratorOpt || (!*RangeIteratorOpt && !bLast))
        {
            const auto ListParentKey = Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                Self->NamespaceName,
                "StoreContentModelMaster"
            );

            if (!RangeIteratorOpt)
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Money2::Model::FStoreContentModelMaster>(ListParentKey);

                if (Range)
                {
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    PageToken = TOptional<FString>();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Future = Self->Client->DescribeStoreContentModelMasters(
                MakeShared<Gs2::Money2::Request::FDescribeStoreContentModelMastersRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithPageToken(PageToken)
                    ->WithLimit(FetchSize)
            );
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
            Range = R->GetItems();
            for (auto Item : *R->GetItems())
            {
                Self->Gs2->Cache->Put(
                    Gs2::Money2::Model::FStoreContentModelMaster::TypeName,
                    ListParentKey,
                    Gs2::Money2::Domain::Model::FStoreContentModelMasterDomain::CreateCacheKey(
                        Item->GetName()
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (Range)
            {
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
            if (bLast) {
                Self->Gs2->Cache->SetListCached(
                    Gs2::Money2::Model::FStoreContentModelMaster::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeStoreContentModelMastersIterator::FIterator FDescribeStoreContentModelMastersIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeStoreContentModelMastersIterator::FIterator FDescribeStoreContentModelMastersIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeStoreContentModelMastersIterator::FIterator FDescribeStoreContentModelMastersIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
