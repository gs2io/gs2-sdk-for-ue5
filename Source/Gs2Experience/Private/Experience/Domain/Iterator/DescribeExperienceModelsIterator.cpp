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

#include "Experience/Domain/Iterator/DescribeExperienceModelsIterator.h"
#include "Experience/Domain/Model/ExperienceModel.h"
#include "Experience/Domain/Model/Namespace.h"

namespace Gs2::Experience::Domain::Iterator
{

    FDescribeExperienceModelsIterator::FDescribeExperienceModelsIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Experience::FGs2ExperienceRestClientPtr Client,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeExperienceModelsIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Experience::Model::FExperienceModel>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeExperienceModelsIterator::FIterator::FIterator(
        const TSharedRef<FDescribeExperienceModelsIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeExperienceModelsIterator::FIterator& FDescribeExperienceModelsIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Experience::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            Self->NamespaceName,
            "ExperienceModel"
        );
            if (Self->Cache->IsListCached(
                Gs2::Experience::Model::FExperienceModel::TypeName,
                ListParentKey
            )) {
                Range = MakeShared<TArray<Gs2::Experience::Model::FExperienceModelPtr>>();
                *Range = Self->Cache->List<Gs2::Experience::Model::FExperienceModel>(
                    ListParentKey
                );
                RangeIteratorOpt = Range->CreateIterator();
                bLast = true;
                bEnd = static_cast<bool>(*RangeIteratorOpt);
                return *this;
            }
            const auto Future = Self->Client->DescribeExperienceModels(
                MakeShared<Gs2::Experience::Request::FDescribeExperienceModelsRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
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
                    Gs2::Experience::Model::FExperienceModel::TypeName,
                    ListParentKey,
                    Gs2::Experience::Domain::Model::FExperienceModelDomain::CreateCacheKey(
                        Item->GetName()
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            RangeIteratorOpt = Range->CreateIterator();
            bLast = true;
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeExperienceModelsIterator::FIterator FDescribeExperienceModelsIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeExperienceModelsIterator::FIterator FDescribeExperienceModelsIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeExperienceModelsIterator::FIterator FDescribeExperienceModelsIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

