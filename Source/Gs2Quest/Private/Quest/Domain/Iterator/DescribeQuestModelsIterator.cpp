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

#include "Quest/Domain/Iterator/DescribeQuestModelsIterator.h"
#include "Quest/Domain/Model/QuestModel.h"
#include "Quest/Domain/Model/QuestGroupModel.h"

namespace Gs2::Quest::Domain::Iterator
{

    FDescribeQuestModelsIterator::FDescribeQuestModelsIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Quest::FGs2QuestRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> QuestGroupName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName),
        QuestGroupName(QuestGroupName)
    {
    }

    FDescribeQuestModelsIterator::FDescribeQuestModelsIterator(
        const FDescribeQuestModelsIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        QuestGroupName(From.QuestGroupName)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeQuestModelsIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Quest::Model::FQuestModel>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeQuestModelsIterator::FIterator::FIterator(
        const TSharedRef<FDescribeQuestModelsIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeQuestModelsIterator::FIterator& FDescribeQuestModelsIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Quest::Domain::Model::FQuestGroupModelDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->QuestGroupName,
                "QuestModel"
            );

            if (!RangeIteratorOpt)
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Quest::Model::FQuestModel>(ListParentKey);

                if (Range)
                {
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Future = Self->Client->DescribeQuestModels(
                MakeShared<Gs2::Quest::Request::FDescribeQuestModelsRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithQuestGroupName(Self->QuestGroupName)
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
                    Gs2::Quest::Model::FQuestModel::TypeName,
                    ListParentKey,
                    Gs2::Quest::Domain::Model::FQuestModelDomain::CreateCacheKey(
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
            bLast = true;
            if (bLast) {
                Self->Gs2->Cache->SetListCached(
                    Gs2::Quest::Model::FQuestModel::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeQuestModelsIterator::FIterator FDescribeQuestModelsIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeQuestModelsIterator::FIterator FDescribeQuestModelsIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeQuestModelsIterator::FIterator FDescribeQuestModelsIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

