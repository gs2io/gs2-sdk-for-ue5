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

#include "CoreMinimal.h"
#include "Lottery/Domain/Model/Namespace.h"
#include "Lottery/Model/Gs2LotteryEzLotteryModel.h"
#include "Util/Net/GameSession.h"

namespace Gs2::UE5::Lottery::Domain::Iterator
{

	class EZGS2_API FEzDescribeLotteryModelsIterator :
        public TSharedFromThis<FEzDescribeLotteryModelsIterator>
    {
        Gs2::Lottery::Domain::Iterator::FDescribeLotteryModelsIteratorPtr It;
        Gs2::Lottery::Domain::Model::FNamespaceDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr Connection;

	public:

        explicit FEzDescribeLotteryModelsIterator(
            Gs2::Lottery::Domain::Model::FNamespaceDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        ) :
            It(
                Domain->LotteryModels(
                )
            ),
            Domain(Domain),
            Connection(Connection)
        {
        }

		FEzDescribeLotteryModelsIterator(
			const FEzDescribeLotteryModelsIterator& From
		) :
			It(From.It),
			Domain(From.Domain),
			Connection(From.Connection)
		{
		}

		class EZGS2_API FIterator
		{
		    friend class FEzDescribeLotteryModelsIterator;

			Gs2::Lottery::Domain::Iterator::FDescribeLotteryModelsIterator::FIterator DomainIterator;
			Gs2::UE5::Lottery::Model::FEzLotteryModelPtr CurrentValue;
        	static Gs2::UE5::Lottery::Model::FEzLotteryModelPtr ConvertCurrent(
        		Gs2::Lottery::Domain::Iterator::FDescribeLotteryModelsIterator::FIterator& DomainIterator
        	)
        	{
				return DomainIterator.IsCurrentValid()
	    			? Gs2::UE5::Lottery::Model::FEzLotteryModel::FromModel(DomainIterator.Current())
					: nullptr;
        	}

			explicit FIterator(
				Gs2::Lottery::Domain::Iterator::FDescribeLotteryModelsIterator::FIterator&& DomainIterator
			) :
			    DomainIterator(DomainIterator),
			    CurrentValue(ConvertCurrent(DomainIterator))
			{}

		public:
			explicit FIterator(
				FEzDescribeLotteryModelsIterator& Iterable
			) :
			    FIterator(Iterable.begin())
			{}

			FIterator(
			    const FIterator& Iterator
            ) :
                DomainIterator(Iterator.DomainIterator),
                CurrentValue(Iterator.CurrentValue)
            {}

			FIterator& operator*()
			{
				return *this;
			}

			const FIterator& operator*() const
			{
				return *this;
			}

			FIterator* operator->()
			{
				return this;
			}

			const FIterator* operator->() const
			{
				return this;
			}

			FIterator& operator++()
			{
				++DomainIterator;
				CurrentValue = ConvertCurrent(DomainIterator);
				return *this;
			}
            Gs2::UE5::Lottery::Model::FEzLotteryModelPtr& Current()
            {
                return CurrentValue;
            }

            Gs2::Core::Model::FGs2ErrorPtr Error()
            {
                return DomainIterator.Error();
            }

            bool IsError() const
            {
                return DomainIterator.IsError();
            }

            void Retry()
            {
                DomainIterator.Retry();
            }

			friend bool operator== (const FIterator& a, const FIterator& b)
			{
				return a.DomainIterator == b.DomainIterator;
			}
			friend bool operator!= (const FIterator& a, const FIterator& b)
			{
				return !operator==(a, b);
			}
		};

		FIterator OneBeforeBegin()
		{
			return FIterator(It->OneBeforeBegin());
		}
		FIterator begin()
		{
			return FIterator(It->begin());
		}
		FIterator end()
		{
			return FIterator(It->end());
		}
    };
	typedef TSharedPtr<FEzDescribeLotteryModelsIterator> FEzDescribeLotteryModelsIteratorPtr;
}
