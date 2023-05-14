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

#include "Stamina/Domain/Iterator/DescribeStaminaModelMastersIterator.h"
#include "Stamina/Domain/Model/StaminaModelMaster.h"
#include "Stamina/Domain/Model/Namespace.h"

namespace Gs2::Stamina::Domain::Iterator
{

    FDescribeStaminaModelMastersIterator::FDescribeStaminaModelMastersIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Stamina::FGs2StaminaRestClientPtr Client,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeStaminaModelMastersIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FStaminaModelMaster>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeStaminaModelMastersIterator::FIterator::FIterator(
        const TSharedRef<FDescribeStaminaModelMastersIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeStaminaModelMastersIterator::FIterator& FDescribeStaminaModelMastersIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            Self->NamespaceName,
            "StaminaModelMaster"
        );
            if (Self->Cache->IsListCached(
                Gs2::Stamina::Model::FStaminaModelMaster::TypeName,
                ListParentKey
            )) {
                Range = MakeShared<TArray<Gs2::Stamina::Model::FStaminaModelMasterPtr>>();
                *Range = Self->Cache->List<Gs2::Stamina::Model::FStaminaModelMaster>(
                    ListParentKey
                );
                RangeIteratorOpt = Range->CreateIterator();
                PageToken = TOptional<FString>();
                bLast = true;
                bEnd = static_cast<bool>(*RangeIteratorOpt);
                return *this;
            }
            const auto Future = Self->Client->DescribeStaminaModelMasters(
                MakeShared<Gs2::Stamina::Request::FDescribeStaminaModelMastersRequest>()
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
                Self->Cache->Put(
                    Gs2::Stamina::Model::FStaminaModelMaster::TypeName,
                    ListParentKey,
                    Gs2::Stamina::Domain::Model::FStaminaModelMasterDomain::CreateCacheKey(
                        Item->GetName()
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeStaminaModelMastersIterator::FIterator FDescribeStaminaModelMastersIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeStaminaModelMastersIterator::FIterator FDescribeStaminaModelMastersIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeStaminaModelMastersIterator::FIterator FDescribeStaminaModelMastersIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

